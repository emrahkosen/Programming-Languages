const request = require('request');
var testWithGivenKey = require("./modules/testWithGivenKey");




Promise.resolve(process.argv[2]).then(function(key)
{
  if(key)
    testWithGivenKey(key);
  else
  {
    testWithGivenKey("rest")
  }
})
