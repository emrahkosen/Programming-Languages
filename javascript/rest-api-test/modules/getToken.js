const request = require('request');

async function getToken()
{
  var token = "jwt ";
  var options =
  { method: 'GET',
    url: 'https://apidev.matriksdata.com:30443/login',
    agentOptions: {
      rejectUnauthorized: false
    },
    headers:
     { 'Postman-Token': '17154bcb-1391-493b-a6dd-63d3c81dccc6',
       'cache-control': 'no-cache',
       'X-Client-Type': 'D',
       Authorization: 'Basic MjAwMDAxOnN0YWox'
     }
  };
  return new Promise((resolve, reject) => {
    request(options, function (error, response, body) {
      if (error) reject(error);
      var obody = JSON.parse(body);
      token += obody.token;
      resolve(token)

    });
  })

}

module.exports = getToken;
