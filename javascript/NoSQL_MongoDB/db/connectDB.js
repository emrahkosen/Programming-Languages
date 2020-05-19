const express = require("express");
var mongo = require('mongodb');
var MongoClient = require('mongodb').MongoClient;
const url = "mongodb+srv://emrah:123@cluster0-agpcm.mongodb.net/test?retryWrites=true&w=majority";



async function insertData(myobj,dataB,collect)
{
   const client = await MongoClient.connect(url, {useUnifiedTopology: true, useNewUrlParser: true })
       .catch(err => { console.log(err); });

   if (!client) {
       return;
   }

   try {

       const db = client.db(dataB);

       let collection = db.collection(collect);

       res = await collection.insertOne(myobj);


     } catch (err) {

       console.log(err);
     } finally {

       client.close();
     }
}


function insertAll(myobj,dataB,collect)
{
  MongoClient.connect(url, function(err, db) {
  if (err) throw err;
  var dbo = db.db(dataB);
  dbo.collection(collect).insertMany(myobj, function(err, res) {
    if (err) throw err;
    console.log("Number of documents inserted: " + res.insertedCount);
    db.close();
  });
});
}


async function findAll(dataB,collect)
{
  const client = await MongoClient.connect(url, {useUnifiedTopology: true, useNewUrlParser: true })
      .catch(err => { console.log(err); });

    const db = client.db(dataB);
    const MyCollection = db.collection(collect);
    const result = await MyCollection.find({}).toArray();
    client.close();
    return result;
}


async function findOne(query,dataB,collect) {
    let res = {};
    const client = await MongoClient.connect(url, {useUnifiedTopology: true, useNewUrlParser: true })
        .catch(err => { console.log(err); });

    if (!client) {
        return;
    }

    try {

        const db = client.db(dataB);

        let collection = db.collection(collect);

        res = await collection.findOne(query);


    } catch (err) {

        console.log(err);
    } finally {

        client.close();
    }
    return res;
}


async function deleteOne(query,dataB,collect)
{

const client = await MongoClient.connect(url, {useUnifiedTopology: true, useNewUrlParser: true })
    .catch(err => { console.log(err); });

if (!client) {
    return;
}

try {

    const db = client.db(dataB);

    let collection = db.collection(collect);

    res = await collection.deleteOne(query);


  } catch (err) {

    console.log(err);
  } finally {

    client.close();
  }
}


async function find_update(user,dataB,collect)
{
  const client = await MongoClient.connect(url, {useUnifiedTopology: true, useNewUrlParser: true })
      .catch(err => { console.log(err); });

    const db = client.db(dataB);
    const MyCollection = db.collection(collect);
    let newvalues = {$set: { rating: user.rating,
                             rating_count: user.rating_count,
                             avg_rating: user.avg_rating,
                             gallery: user.gallery} };
    const result = await MyCollection.findOneAndUpdate({name: user.name },newvalues );
    client.close();
    return result;
}


module.exports.deleteOne = deleteOne;
module.exports.findOne = findOne;
module.exports.findAll = findAll;
module.exports.insertAll = insertAll;
module.exports.insertData = insertData;
module.exports.find_update = find_update;
