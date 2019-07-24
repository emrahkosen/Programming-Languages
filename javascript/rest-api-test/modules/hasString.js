function hasString(obj)
{
  for(var e in obj)
  {
    if((typeof obj[e]) == "string")
      return true;
  }
  return false;
}

module.exports = hasString;
