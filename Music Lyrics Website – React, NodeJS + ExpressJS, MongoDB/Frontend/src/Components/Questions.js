import React from 'react';
import axios from 'axios';
import 'bootstrap/dist/css/bootstrap.min.css';
import Menu from './Menu';

class Questions extends React.Component {

    constructor(props){
        super(props);
		this.state={
            questions: []
		}
	}

    componentDidMount() {
        this.fetchData();
    }

    fetchData() {
        axios.get(`http://localhost:3000/api/v1/questions`)
		.then((response) => {
            this.setState({questions: response.data});
		})
		.catch(error => alert("Error adding questions"));
    }

    deleteQuestion = (id) => {
        axios.delete(`http://localhost:3000/api/v1/questions/${id}`)
        .then((response) => {
            this.fetchData();
        })
        .catch(error => alert("Error deleting songs"));
    }
    
    answerQuestion = (id) => {
        const a = {
            answer : document.getElementById(id).value
        }
        axios.put(`http://localhost:3000/api/v1/questions/${id}`, a)
		.then((response) => {
            this.fetchData()
		})
        .catch(error => {
            alert("Error answering")
        });
    }

    starrQuestion = (id) => {
        axios.put(`http://localhost:3000/api/v1/questions/starr/${id}`)
		.then((response) => {
            this.fetchData()
            alert('Message added to favorites')
		})
        .catch(error => {
            alert("Error starring question")
        });
    }

    unstarrQuestion = (id) => {
        axios.put(`http://localhost:3000/api/v1/questions/unstarr/${id}`)
		.then((response) => {
            this.fetchData()
            alert('Message removed from favorites')
		})
        .catch(error => {
            alert("Error starring question")
        });
    }

    render() {
        return (
            <div className='full-width-container'>
                <Menu></Menu>
                <br></br>
                {this.state.questions.map((question, index) => 
                    <div key={index}>
                        <div className='faq-questions'>
                            <p className="authorEmail">{question.authorEmail}</p>
                            <p className="question1">{question.report}</p>
                            <p className="answer">{question.answer}</p>
                        </div>
                        <br></br>
                        <label className='label-questions' htmlFor="answer">Your answer: </label>
                        <br></br>
                        <textarea className='input-textarea' id={question._id} name={question._id} rows={2} style={{minWidth: 340}}></textarea>
                        <br></br>
                        <button className='temp-add-artists' onClick={() => this.answerQuestion(question._id)}>Answer</button>
                        <button className='temp-add-artists' onClick={() => this.deleteQuestion(question._id)}>Delete</button>
                        <button className='temp-add-artists' onClick={() => this.starrQuestion(question._id)}>Favorite</button>
                        <button className='temp-add-artists' onClick={() => this.unstarrQuestion(question._id)}>Remove Favorite</button>
                    </div>
                )}
            </div>
        );
    }
};

export default Questions;