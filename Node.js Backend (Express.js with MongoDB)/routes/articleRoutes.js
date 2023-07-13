import express from 'express';
import {readArticles, createArticle, readArticle, updateArticle, deleteArticle} 
       from '../controllers/articleController.js';

const router = express.Router();

router.route('/').get(readArticles).post(createArticle);
router.route('/:id').get(readArticle).put(updateArticle).delete(deleteArticle);

const articleRoutes = router;
export {articleRoutes};
