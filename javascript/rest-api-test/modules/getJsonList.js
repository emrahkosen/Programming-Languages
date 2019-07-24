const request = require('request');


function getjsonlist(url,token)
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
      { 'Postman-Token': '5616d033-9d99-486e-aac8-363bc3734496',
        'cache-control': 'no-cache',
        Authorization: token
      }

    };
    request(options,function(error,response,body)
    {
      if(error)
        reject(error);
      var bd = JSON.parse(body);
      console.log(bd);
      resolve(bd);
    })
  })

}


module.exports = getjsonlist;
