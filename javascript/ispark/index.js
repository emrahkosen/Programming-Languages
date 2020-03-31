var bodyParser = require('body-parser');
var express = require('express');
let ejs = require('ejs');
var app = express();
var cors = require('cors');
var path = require('path');
var port = process.env.PORT || 8000

var getjsonlist = require("./getJsonList");



app.use(bodyParser());
app.use(cors());


app.set('views',path.join(__dirname,'./views'));
app.set('view engine', 'ejs');



 function DistrictCarParks(ilce, len, body)
  {
    let ret = "";
    for(let i = 0;i < len; i++)
    {
      if(body[i].Ilce == ilce)
      {
        ret += body[i].ParkAdi + '</br>';
        //console.log(body[i].ParkAdi)
      }
    }
    return ret;

  };

  function freeParkingPpaces(parkname,len,body)
  {

    for(let i = 0; i < len; i++ )
    {
      if(body[i].ParkAdi == parkname)
      {
        return [("Park Name: "+ body[i].ParkAdi + "</br>  Location: " + body[i].Ilce +  "</br>  Free Space: " + body[i].Kapasitesi + "</br>"), parseFloat(body[i].Longitude), parseFloat(body[i].Latitude ) ];
      }
    }
  };

  function ilceler(len, body)
  {
    let liste = [];
    let ret = "";
    for(let i= 0; i < len; i++)
    {
      if(!liste.includes(body[i].Ilce))
      {
          liste.push(body[i].Ilce);
          ret += body[i].Ilce + "</br>"
      }
    }
    return ret;
  };


app.get('/', (request,response)=>{
  response.render('index',{ilce: "",
                           parklar: "",
                           park: "",
                           long: 29.11,
                           lat: 40.88,
                           zooming: 9,
                           heights: 100});
});


app.post('/ilceler',async (req,res)=>
{
  let body = await getjsonlist('https://api.ibb.gov.tr/ispark/Park');
  let len = body.length;

  ret = ilceler(len, body);

  res.render('',{
      ilce: ret,
      park: "",
      parklar: "",
      long: 29.11,
      lat: 40.88,
      zooming: 9,
      heights: 700
  });
})



app.post('/ilce',async (req,res)=>
{
  let inp = req.body.inp;
  let body = await getjsonlist('https://api.ibb.gov.tr/ispark/Park');
  let len = body.length;
  let height_tmp = 1200
  ret = DistrictCarParks(inp, len, body);
  if(inp == "FATİH" || inp == "BEŞİKTAŞ")
    height_tmp = 2000
  res.render('',{
      ilce: "",
      park: "",
      parklar: ret,
      long: 29.11,
      lat: 40.88,
      zooming: 9,
      heights: height_tmp
  });
})

app.post('/park',async (req,res)=>
{
  let park = req.body.park;
  let body = await getjsonlist('https://api.ibb.gov.tr/ispark/Park');
  let len = body.length;

  ret = freeParkingPpaces(park,len,body);

  res.render('',{
      ilce: "",
      parklar: "",
      park: ret[0],
      long: ret[1],
      lat: ret[2],
      zooming: 16,
      heights: 150
  });
})

app.listen(port,()=>{console.log("port: 8000")})
