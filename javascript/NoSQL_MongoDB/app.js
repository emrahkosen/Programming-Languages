var express = require('express');
var app = express();
var ejs = require('ejs');
var bodyParser = require('body-parser');
var cors = require('cors');

const db = require('./db/connectDB');

var port = process.env.PORT || 8000



app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended: true}));
app.set('views', '');
app.set('view engine', 'ejs')
app.use(cors());

const request = require('request');

let users = [];
let user = {};
let ids = 0;
let dataB = "hw2";
let collect = "ceng495";


app.get('/', async (req,res) => {

    res.render('',{
        empty: "no",
        method: "no",
        users: users
    });
});

app.post('/method',async (req,res) => {
    let input = req.body.input;
    users = await db.findAll(dataB,collect);
        res.render('',
        {
            method: input,
            users: users
        });

});


app.post('/adduser',async (req,res) => {
    let username = req.body.name;
    let canadd = true;
    for(i =0;  i < users.length; i++)
        if(users[i].name == username)
            canadd = false;
    if(req.body.name.includes(" ") > 0)
        canadd = false;

    if(canadd == true && username != "")
    {
        let myobj = {
                        name: username,
                        rating: 0,
                        rating_count:0,
                        avg_rating:0,
                        gallery: []
                     }
         db.insertData(myobj,dataB,collect);
      }

        res.render('',
        {
            users: users,
            method: "no"
        });

});

app.post('/deluser',async (req,res) => {

console.log(req.body.name);

        if(Object.keys(req.body).length)
        {
            let query = {name: req.body.name}
            await db.deleteOne(query,dataB,collect);

        }
        users = await db.findAll(dataB,collect);
        res.render('',
        {
            users: users,
            method: "no"
        });

});



app.post('/login',async (req,res) => {

    let method4 = "login";
    if( Object.keys(req.body).length )
    {
        method4 = "user";
        let query = {name: req.body.name};
        user = await db.findOne(query,dataB,collect);
        console.log( user);
    }
    else
      user = {};

    users = await db.findAll(dataB,collect);
        res.render('',
        {
            users: users,
            user:user,
            method: method4,
            usermethod: "no"
        });

});




app.post('/user_method',async (req,res) => {
  let user_method = "";
  let query = {name: user.name};
  user = await db.findOne(query,dataB,collect);
  if( Object.keys(req.body).length )
  {

    res.render('',
    {
        users: users,
        user:user,
        method: "user",
        usermethod: req.body.method
    });
  }
  else
  {
    res.render('',
    {
        users: users,
        user:user,
        method: "user",
        usermethod: "no"
    });
  }
});

app.post('/exibit',async (req,res) =>
{
    let canadd = 1;
    for(let i = 0 ; i<user.gallery.length; i++ )
      if(user.gallery[i].product == req.body.product)
        canadd = 0;
    if(req.body.product.includes(" ") > 0 || req.body.product == '' )
        canadd = 0;

    if(canadd == 1)
    {


        let invention = { active:1,
                            product:req.body.product,
                            photo:req.body.photo,
                            cost:req.body.cost,
                            materials:req.body.materials,
                            inventors:req.body.inventors,
                            rating: 0,
                            rated_users: {}
                          };

      if(req.body.feature1name != '' )
        invention[req.body.feature1name] = req.body.feature1;

      if(req.body.feature2name != '' )
          invention[req.body.feature2name] = req.body.feature2;

      await db.deleteOne(user,dataB,collect);
      user.gallery.push(invention);
      await db.insertData(user,dataB,collect);
      //  user = users[i];
      users = await db.findAll(dataB,collect);

      }

    res.render('',
    {
        users: users,
        user:user,
        method: "user",
        usermethod: "no"
    });

});

app.post('/drop',async (req,res) => {
    let product = req.body.product;

    let query = {name: user.name};
    await db.deleteOne(query,dataB,collect);

        for(let j = 0; j < user.gallery.length; j++ )
        {

          if(user.gallery[j].product == product)
          {
            user.gallery[j].active = 0;
          }
        }
      await db.insertData(user,dataB,collect);
      users = await db.findAll(dataB,collect);

    res.render('',
    {
        users: users,
        user:user,
        method: "user",
        usermethod: "no"
    });

});



let product = [];
app.post('/show',async (req,res) =>
{
  if( req.body['product'] && req.body.product != '' )
  {

      let indis = 0;
      product = req.body.product.split(',');
      let query = {name: product[1]};
      let user2 = await db.findOne(query,dataB,collect);
      for(let j = 0; j < user2.gallery.length; j++ )
      {
        if(user2.gallery[j].product == product[0] )
        {
          indis = j;
          break;
        }
      }

      res.render('',
      {
          users: users,
          user:user,
          product:user2.gallery[indis],
          method: "user",
          usermethod: "show"
      });
    }
  else
  {
    res.render('',
    {
        users: users,
        user:user,
        method: "user",
        usermethod: "no"
    });
  }
});

app.post('/rate',async (req,res) => {

    if( req.body['quantity']  )
    {

        let query = {name: product[1]};
        let user2 = await db.findOne(query,dataB,collect);
        let quantity = parseInt(req.body.quantity);

        //await db.deleteOne(query,dataB,collect);

            for(let j = 0; j < user2.gallery.length; j++ )
            {
              if(user2.gallery[j].product == product[0] )
              {
                if(user2.gallery[j].rated_users[ user.name ])// if exist
                {
                  console.log("update");

                  user2.rating -= user2.gallery[j].rated_users[user.name];
                  user2.gallery[j].rating -= user2.gallery[j].rated_users[user.name];
                  user2.gallery[j].rated_users[user.name] = quantity;
                  user2.rating += quantity;
                  user2.gallery[j].rating += quantity;
                  user2.avg_rating = user2.rating/user2.rating_count;

                }
                else
                {
                  console.log("new");
                  user2.gallery[j].rated_users[user.name] = quantity;
                  user2.rating += quantity;
                  user2.gallery[j].rating += quantity;
                  user2.rating_count += 1;
                  user2.avg_rating = user2.rating/user2.rating_count;

                }
          //       await db.insertData(user2,dataB,collect);
                 await db.find_update(user2,dataB,collect);
                console.log( user2 );
                //sum new value to rate then subst the old valueto rate
              }
            }

      }
    let query = {name: user.name};
    user = await db.findOne(query,dataB,collect);
    users = await db.findAll(dataB,collect);
    console.log(user);
    res.render('',
    {
        users: users,
        user:user,
        method: "user",
        usermethod: "no"
    });

});


app.listen(port, () => {
    console.log('listening localhost:8000');
});
