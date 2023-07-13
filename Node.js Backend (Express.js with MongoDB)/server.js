import express from 'express';
import mongoose from 'mongoose';
import cors from 'cors';

import {articleRoutes} from './routes/articleRoutes.js';

const app = express();

app.use(express.json({ limit: "20mb", extended: true }));
app.use(express.urlencoded({ limit: "20mb", extended: true }));
app.use(cors());

app.use('/rest_api/articles', articleRoutes);

const databaseLink = 'mongodb+srv://<username>:<password>@cluster0blogapp.xogvqx6.mongodb.net/?retryWrites=true&w=majority';
const port = process.env.PORT || 3000;

const connectDatabase = async () => {
    try {
        const conn = await mongoose.connect(databaseLink);
        console.log(`Database is connected.`);   //if we have a successfull database connection.
    } catch (error) {
        console.log(error.message);   //if the database connection is unsuccessful.
        process.exit(1);
    }
    };
connectDatabase();
app.listen(port, () => console.log(`The server is running on port ${port}, starting at ${Date()}.`))