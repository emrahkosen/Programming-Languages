#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<sys/socket.h>

#include<sys/select.h>
#include<sys/wait.h>
#include<sys/time.h>

#include "lib/message.h"
#include "lib/logging.h"

#define PIPE(a) socketpair(AF_UNIX, SOCK_STREAM,PF_UNIX,(a))





int main()
{
    char lines[100];
    char newString[3][10];
    int i,j,ctr;
    int first_line[3];

/*********get first line and split it***************************/
    fgets(lines, sizeof lines, stdin);
    j=0; ctr=0;
    for(i=0;i<=(strlen(lines));i++)
    {
        // if space or NULL found, assign NULL into newString[ctr]
        if(lines[i]==' '||lines[i] == '\0')
        {
            newString[ctr][j]='\0';

            first_line[ctr] = atoi(newString[ctr]);
            ctr++;  //for next word
            j=0;    //for next word, init index to 0

        }
        else
        {
            newString[ctr][j]=lines[i];
            j++;
        }
    }

/**********************************************************************/
/**********************************************************************/


    int socket[first_line[2]][2]; // after getting from bidder nomber create that # of socket
    int child[first_line[2]];
    char *arrays[ first_line[2] ];

    for(i = 0; i< first_line[2]; i++) // creafe bidder # times child proccess and exec it
    {
      PIPE(socket[i]);
      fgets(lines, sizeof lines, stdin);

      char *wordf = strtok(lines, " \n");
      arrays[i] = wordf;

      wordf = strtok(NULL, " \n");
      char *argv[ atoi(wordf) + 1];


      int h = 0;
      argv[h++] = arrays[i]; //executable bidder

      wordf = strtok(NULL, " \n");
      while(wordf != NULL)
      {
        argv[h++] = wordf;
        wordf = strtok(NULL, " \n"); // add avg parameters to executable
      }

      argv[h] = NULL;


      child[i] = fork();

      if(child[i] == 0)
      {
        int t;

        for ( t = 0; t < first_line[2]; t++)// close all socket exept ith one's 0th side
        {
          close(socket[t][1]);
          if(i != t)
            close(socket[t][0]);
        }

        dup2(socket[i][0],1); //open stdout
        dup2(socket[i][0],0); //open stdin

        close(socket[i][0]);
        execv(argv[0],argv);

        exit(1);
      }

      else
      {

        continue;

      }
    }


/**********************************************************************/
/**********************************************************************/







////////////////////////////////////////////////////////////////////////////////
cm a[first_line[2]];
sm start;
int clienFinished[first_line[2]];
int statuses[first_line[2]];
int clienFinishedNo = 0;



int max_file_desc = 0;
fd_set readset;


start.message_id = 1;
start.params.start_info.client_id = 0; //from i to first_line[2]-1 and it represend higest bid owner
start.params.start_info.starting_bid = first_line[0];
start.params.start_info.current_bid = first_line[0];
start.params.start_info.minimum_increment = first_line[1];


////////////////////////////////////////////////////////////////////////////////


    for ( i = 0; i < first_line[2]; i++)// Close all socket 0th side
    {
      close(socket[i][0]);
      clienFinished[i] = 0;
      if(socket[i][1] > max_file_desc)
        max_file_desc = socket[i][1];
    }

max_file_desc = max_file_desc + 1;


    while(1)
    {

//************************************************************************/
      FD_ZERO(&readset);
      for ( i = 0; i < first_line[2]; i++)
      {
        if (clienFinished[i] == 0)
          FD_SET(socket[i][1],&readset);
      }

      select(max_file_desc, &readset, NULL,NULL,NULL);

        for ( i = 0; i < first_line[2]; i++)// read CLIENT_CONNECT message from bidders for each
        {                                   //and send SERVER_CONNECTION_ESTABLISHED messages

          if (!FD_ISSET(socket[i][1], &readset))
            continue;

            /*******************************************************************************/


          if(clienFinished[i] == 0)//if not finished
          {

            if (read(socket[i][1], &a[i], sizeof(a[i])) < 0)
                 {
                       perror("reading stream message");
                 }


            /*****************************************/
            /*****************************************/
            ii printInput;
            printInput.type = a[i].message_id;//TODO
            printInput.pid = child[i];
            printInput.info = a[i].params;
            print_input(&printInput, i);
            /*****************************************/
            /*****************************************/

              if(a[i].message_id == CLIENT_CONNECT)
              {
                start.params.start_info.client_id = i; //from i to first_line[2]-1

                if ( write(socket[i][1], &start, sizeof(start) ) < 0) //SERVER_CONNECTION_ESTABLISHED
                  {
                      perror("writing stream message");
                  }


                    /*****************************************/
                    /*****************************************/
                    oi printOutput;
                    printOutput.type = start.message_id;
                    printOutput.pid = child[i];
                    printOutput.info = start.params;
                    print_output(&printOutput, i);
                    /*****************************************/
                    /*****************************************/

              }

              else if ( a[i].message_id == CLIENT_BID)
              {
                sm send;

                if(a[i].params.bid < start.params.start_info.starting_bid)
                {
                    send.message_id = SERVER_BID_RESULT;
                    send.params.result_info.result = BID_LOWER_THAN_STARTING_BID;
                    send.params.result_info.current_bid = start.params.start_info.current_bid;
                }
                else if( a[i].params.bid < start.params.start_info.current_bid )
                {
                  send.message_id = SERVER_BID_RESULT;
                  send.params.result_info.result = BID_LOWER_THAN_CURRENT;
                  send.params.result_info.current_bid = start.params.start_info.current_bid;
                }
                else if( a[i].params.bid < start.params.start_info.current_bid + start.params.start_info.minimum_increment)
                {
                  send.message_id = SERVER_BID_RESULT;
                  send.params.result_info.result = BID_INCREMENT_LOWER_THAN_MINIMUM;
                  send.params.result_info.current_bid = start.params.start_info.current_bid;
                }

                else
                {

                  send.message_id = SERVER_BID_RESULT;
                  send.params.result_info.result = BID_ACCEPTED;
                  send.params.result_info.current_bid = a[i].params.bid;

                  start.params.start_info.client_id = i;
                  start.params.start_info.current_bid = a[i].params.bid;
                }

                if ( write(socket[i][1], &send, sizeof(send) ) < 0) //SERVER_CONNECTION_ESTABLISHED
                      {
                        perror("writing stream message");
                      }

                    /*****************************************/
                    /*****************************************/
                    oi printOutput;
                    printOutput.type = send.message_id;
                    printOutput.pid = child[i];
                    printOutput.info = send.params;
                    print_output(&printOutput, i);
                    /*****************************************/
                    /*****************************************/
              }
              else //CLIENT_FINISHED
              {

                statuses[i] = a[i].params.status;
                clienFinished[i] = 1;
                clienFinishedNo++;
              }
          }

        }

          if(clienFinishedNo == first_line[2])
          {
            sm winnerInfo;
            int w;
            winnerInfo.message_id = CLIENT_FINISHED;
            winnerInfo.params.winner_info.winner_id = start.params.start_info.client_id;
            winnerInfo.params.winner_info.winning_bid = start.params.start_info.current_bid;


            print_server_finished(start.params.start_info.client_id, start.params.start_info.current_bid);

            for ( w = 0; w < first_line[2]; w++)
            {
              if ( write(socket[w][1], &winnerInfo, sizeof(winnerInfo) ) < 0) //SERVER_CONNECTION_ESTABLISHED
                  {
                    perror("writing stream message");
                  }

                  /*****************************************/
                  /*****************************************/
                  oi printOutput;
                  printOutput.type = winnerInfo.message_id;
                  printOutput.pid = child[w];
                  printOutput.info = winnerInfo.params;

                  print_output(&printOutput, w);
                  /*****************************************/
                  /*****************************************/


            }

            break;/*after that break sent info about winner for all bidders */
          }
    }




    for (i = 0; i < first_line[2]; i++)
    {
      int status;

      waitpid( child[i], &status, 0);
      print_client_finished(i, status,status == statuses[i]);
    }


    //print TODO

    return 0;
}
