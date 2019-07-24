function readjson(path) //'./rest-api-test/json/data.json'
{
  return new Promise((resolve,reject)=>
  {
    var fs = require('fs');
    fs.readFile(path,'utf8',(err,data)=>
    {
      if(err)
        resolve("error");
      resolve(data);
    });
  })
}


module.exports = readjson;
