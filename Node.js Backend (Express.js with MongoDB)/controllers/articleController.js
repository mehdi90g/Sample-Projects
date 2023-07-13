import {Article_Model} from '../models/articleModel.js';

// Get all the articles in the database
const readArticles = async(req,res) => {
    try {
        const articles = await Article_Model.find();
        res.status(200).json(articles)
    }
    catch(err) {
        res.json(err)
    }
}
 
// Create a new article
const createArticle = async(req,res) => {
    try {
        const article = await Article_Model.create(
            {
                subject: req.body.subject,
                author: req.body.author,
                content: req.body.content
            }
        );
        res.status(200).json(article)
    }
    catch(err) {
        res.json(err)
    }
}



// Get an article with a specific id
const readArticle = async(req,res) => {
    try {
        const article = await Article_Model.findById(req.params.id);
        res.status(200).json(article)
    }
    catch(err) {
        res.status(404).json(err)
    }
}

// Update an article with a specific id
const updateArticle = async(req,res) => {
    try {
        const article = await Article_Model.findById(req.params.id);
        if (!article) return res.status(404).send('Article not found.');

        const updatedArticle = await Article_Model.findByIdAndUpdate(
            req.params.id, 
            req.body,
            {new: true});
        res.status(200).json(updatedArticle)    
    }
    catch(err) {
        res.json(err)
    }
}

// Delete an article with a specific id
const deleteArticle = async(req,res) => {
    try {    
        const article = await Article_Model.findById(req.params.id);
        if (!article) return res.status(404).send('Article not found.');

        await Article_Model.findByIdAndRemove(req.params.id);
        res.status(200).send('Article is deleted.')   
    }
    catch(err) {
        res.json(err)
    }
}
 

export {readArticles, createArticle, readArticle, updateArticle, deleteArticle};