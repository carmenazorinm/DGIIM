import mongoose from 'mongoose';

const USER_DB = process.env.USER_DB;
const PASS = process.env.PASS;
const DB_HOST = process.env.DB_HOST || 'localhost';
const PORT = process.env.PORT || '27017';
const DB = process.env.DB || 'myProject';

const url = `mongodb://${USER_DB}:${PASS}@${DB_HOST}:${PORT}/${DB}?authSource=admin`;

console.log(url);

export default function connectDB() {
  try {
    mongoose.connect(url);
  } catch (err) {
    console.error(err.message);
    process.exit(1);
  }

  const dbConnection = mongoose.connection;
  dbConnection.once('open', () => {
    console.log(`Database connected: ${url}`);
  });

  dbConnection.on('error', (err) => {
    console.error(url);
    console.error(`connection error: ${err}`);
  });
}
