const request = require('request');


function getjsonlist(url)
{

  return new Promise((resolve,reject)=>
  {
    var options =
    {
      method:'GET'
     ,url: url
     ,agentOptions: {
        rejectUnauthorized: false
      }
     ,headers:
      {
      }

    };
    request(options,function(error,response,body)
    {
      if(error)
        reject(error);
      var bd = JSON.parse(body);
      resolve(bd);
    })
  })

}


module.exports = getjsonlist;
