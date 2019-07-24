var getToken = require("./getToken");
var getjsonlist = require("./getJsonList");
var WorkOnObj = require("./workOnObj");
var findobj = require("./findobj");


async function testWithGivenKey(key)
  {

    let token = await getToken();
    let body = await getjsonlist('https://apidev.matriksdata.com:30443/disco-v2.json');
    let objtested;
    let rest = body.rest;
    if(key === "rest")
      {
        objtested =  await WorkOnObj(rest,token)

      }
    else
    {
     let obj = findobj(rest,key);
     if(obj !== null)
        objtested =  await WorkOnObj(obj,token);
    else
      console.log(Error("There is no such key!!"))
    }


    console.log(key,"->", objtested);
};


module.exports = testWithGivenKey;
