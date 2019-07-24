var hasString = require("./hasString");

function findobj(obj,key)
{
  for(let e in obj)
  {
    if(e == key )
      {
        return obj[e];
      }

    if(!( hasString(obj[e]) ) )
      {
        var ret =  findobj(obj[e],key);
        if(ret != null)
          return ret;
      }
  }
  return null;
}



module.exports = findobj;
