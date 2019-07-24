const addparameters = require("../modules/addparameters");
const hasString = require("../modules/hasString");
const getToken = require("../modules/getToken");
const findobj = require("../modules/findobj");
const fget = require("../modules/fget");
const getJsonList = require("../modules/getJsonList");
const WorkOnObj = require("../modules/workOnObj");
const readjson = require("../json/readjson");

describe("Unit test of addparameters" , () =>

{

  let p0 = [];
  let p1 = ["id"];
  let p2 = ["idx"];
  it("Empty parameter array test", ()=>
  {
      let ret = addparameters(p0);
      expect(ret).toBe("?");
  });


  it("Non empty parameter array test", ()=>
  {
      let ret = addparameters(p1);
      expect(ret).toBe("?id=d87bf240-9809-11e9-af5c-6b967b257062&");
  });
  it("Non empty parameter but parameter not in the parameters object test", ()=>
  {
      let ret = addparameters(p2);
      expect(ret).toBe("?idx=&");
  });
});




describe("Unit test of hasString" , () =>

{

  let obj0 = {};
  let obj1 = {a:{}};
  let obj2 = {a:{},b:[1,2,"string"]};
  let obj3 = {a:{},b:[1,2,"string"],c:"string"};
  it("Empty object test", ()=>
  {
      let ret = hasString(obj0);
      expect(ret).toBe(false);
  });

  it("Non empty object which has no string element test", ()=>
  {
      let ret = hasString(obj1);
      expect(ret).toBe(false);
  });

  it("Non empty object which has an array wiht string element test", ()=>
  {
      let ret = hasString(obj2);
      expect(ret).toBe(false);
  });

  it("Non empty object wiht string element test", ()=>
  {
      let ret = hasString(obj3);
      expect(ret).toBe(true);
  });


});



describe("Unit test of getToken" ,  () =>

{
    let originalTimeinterval;
    let token;
    beforeEach( (done) =>
    {
      originalTimeinterval = jasmine.DEFAULT_TIMEOUT_INTERVAL;
      jasmine.DEFAULT_TIMEOUT_INTERVAL = 30000;
      done();
    });



  it("Token type is string", (done)=>
  {
      getToken().then(function(res)
      {
        let token = res;
        console.log("token was taken");
        console.log("expect 1 is starting");
        expect(typeof token).toBe("string");
        console.log("expect 1 finished");
        done();
      });

  });

  it("Token start with jwt ", (done)=>
  {
      getToken().then(function(res)
      {
        let token = res;
        console.log("token was taken");
        let ret = token.substring(0,4);
        console.log("expect 2 is starting");
        expect(ret).toBe("jwt ");
        console.log("expect 2 finished");
        done();
      });


  });

  it("Token length must be greater than 4 ",  (done)=>
  {

    getToken().then(function(res)
    {
      let token = res;
      console.log("token was taken");
      console.log("expect 3 is starting");
      let ret = token.length;
      expect(ret).toBeGreaterThan(4);
      console.log("expect 3 finished");
      done();
    });


  });


});




describe("Unit test of findobj" ,  () =>

{
  let i = 0;
  let ret;
  let objs = [{},{aa:"sdf",b:{a:"11"}},{aa:"sdf",b:{a:"11"}}];
  let keys = ["a","a","aa"];
  let expe = [null,null,"sdf"];

  beforeEach( ( ) =>
  {
    ret = findobj(objs[i],keys[i]);
  });



  it("findobj test empty object", ()=>
  {
      expect(ret).toBe(expe[i++]);
  });

  it("findobj test non empty object given key not included", ()=>
  {
      expect(ret).toBe(expe[i++]);
  });

  it("findobj test non empty object given key included", ()=>
  {
      expect(ret).toBe(expe[i++]);
  });

});




describe("Unit test of fget",  () =>

{
  let urls = ["https://apidev.matriksdata.com:30443/dumrul/v1/foreign-assets?agents=ACA&",
              "https://apidev.matriksdata.com:30443/dumrul/v1/warrant-coach/underlyings"];
  let expe = [false,true];
  let  ret;

  beforeEach( (done) =>
  {
    originalTimeinterval = jasmine.DEFAULT_TIMEOUT_INTERVAL;
    jasmine.DEFAULT_TIMEOUT_INTERVAL = 30000;
    done();
  });



  afterEach( (done) =>
  {
    jasmine.DEFAULT_TIMEOUT_INTERVAL = 5000;
    done();
  });


  it("fget false", (done)=>
  {

    getToken().then(function(token)
    {
      console.log("token was taken 0");
      fget(urls[0],token).then( (ret)=>
      {
          expect(ret).toBe(expe[0]);
          done();
      });
    });

  });


  it("fget true", (done)=>
  {
    getToken().then(function(token)
    {
      console.log("token was taken 1");
      fget(urls[1],token).then( (ret)=>
      {
          expect(ret).toBe(expe[1]);
          done();
      });
    });
  });



});












describe("Unit test of getJsonList",  () =>

{

  beforeEach( (done) =>
  {
    originalTimeinterval = jasmine.DEFAULT_TIMEOUT_INTERVAL;
    jasmine.DEFAULT_TIMEOUT_INTERVAL = 30000;
    done();
  });



  afterEach( (done) =>
  {
    jasmine.DEFAULT_TIMEOUT_INTERVAL = 5000;
    done();
  });


  it("getJsonList true", (done)=>
  {

    getJsonList('https://apidev.matriksdata.com:30443/disco-v2.json').then(function(list)
    {
      console.log(typeof list);
      expect(typeof list).toBe("object");
      done();
    });

  });

});










describe("Unit test of WorkOnObj",  () =>

{
  let obj = require('../json/data.json');

  beforeEach( (done) =>
  {
    originalTimeinterval = jasmine.DEFAULT_TIMEOUT_INTERVAL;
    jasmine.DEFAULT_TIMEOUT_INTERVAL = 30000;
    done();
  });




  afterEach( (done) =>
  {
    jasmine.DEFAULT_TIMEOUT_INTERVAL = originalTimeinterval;
    done();
  });




  it("type false", (done)=>
  {

    // readjson('../json/data.json').then((ret)=>
    // {
    //   console.log(ret);
    // });



    getToken().then(function(token)
    {
      console.log("token was taken 0");
      WorkOnObj(obj,token).then( (ret) =>
      {
          expect(typeof ret).toBe("object");
          done();
      });
    });

  });



});
