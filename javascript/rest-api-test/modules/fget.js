const request = require('request');


async function fget(gurl,token)
{

  return new Promise((resolve,reject)=>
  {
    var options =
    {
      method:'GET'
     ,url: gurl
     ,agentOptions: {
        rejectUnauthorized: false
      }
     ,headers:
      {
        Authorization: token
      }

    };

    request(options, function(error,response,body)
    {
      if(error)
        reject(error);
      var ret = false;
      if(response.statusCode == 200)
        ret = true;
      resolve(ret);

    });
  })
}


module.exports = fget;
