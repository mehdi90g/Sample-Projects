import mongoose from 'mongoose';

// Each article of the blog app, contains a subject, an author, and the content of article.
// timestamps also add the creation and update time and date of each article, in the database.
const articleSchema = mongoose.Schema ( 
    {
        subject: {type: String, required: true},
        author: {type: String},
        content: {type: String}
    },
    { timestamps: true }
)

export const Article_Model = mongoose.model('Article_Model', articleSchema)
