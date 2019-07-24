var hasString = require("./hasString");
var addparameters = require("./addparameters");
var fget = require("./fget");


async function WorkOnObj(obj,token)
{

  let retu = {};

  if( hasString(obj) )
  {

    if(!("method" in obj))
    {
      var ret = {};
      var url = obj["url"];
      if(obj["parameters"].length)
        url += addparameters(obj["parameters"] );
      let lastbody = await fget(url,token);

      return new Promise(function(resolve,reject)
      {

          ret[url] = lastbody;
          resolve(ret);
        });
    }
    else {
      return Promise.resolve(ret);
    }
  }
  else
  {

    return new Promise(async function(resolve,reject)
    {
      let obj2 = {};
      for(let e in obj)
        {
          let res = await WorkOnObj(obj[e],token);
          Object.assign(obj2,res);
        }

        resolve(obj2);

    });

  }

}


module.exports = WorkOnObj;
