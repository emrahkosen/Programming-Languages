var parameters =
{
  "symbol": "GARAN",
  "symbols": "GARAN,AKBNK,AEFES",
  "alpha": "3",
  "days": "155",
  "start": "2018-01-05",
  "end": "2018-01-19",
  "period": "1day",
  "amount": "",
  "count": "50",
  "date": "2018-01-01",
  "agent": "ACA",
  "agents": "ACA",
  "query": "",
  "language": "",
  "count": "",
  "withComment": "",
  "page": "0",
  "pageSize": "10",
  "id": "d87bf240-9809-11e9-af5c-6b967b257062",
  "qid": "d87bf240-9809-11e9-af5c-6b967b257062",
  "underlyings":"EURUSD",
  "content": "false",
  "inline": "true",
  "top": "5",
  "startdate": "2019-01-01",
  "enddate": "2019-05-01",
  "type": "decreasing"
}

function addparameters(param)
{

    var  ret = "?";
    for(var par of param)
      {
        if(!(par in parameters))
          ret += par + "=&";
        else
          ret += par+"="+ parameters[par] + "&";
      }
    return ret;

}

module.exports = addparameters;
