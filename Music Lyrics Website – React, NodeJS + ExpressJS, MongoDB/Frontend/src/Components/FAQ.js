import React from 'react';
import axios from 'axios';
import 'bootstrap/dist/css/bootstrap.min.css';
import Menu from './Menu';

class FAQ extends React.Component {

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
		.then(async (response) => {
            this.setState({questions: response.data});
            const array1 = this.state.questions
            let array2 = array1.filter( function (a) { //doar questions cu starred = true
                return a.starred === true
            });
            array2.sort((a, b) => (a.report[0] > b.report[0]) ? 1 : -1) //sortez dupa question.report alfabetic
            this.setState({questions: array2});
		})
		.catch(error => alert("Error adding questions"));
    }

    render() {
        return (
            <div className='full-width-container'>
                <Menu></Menu>
                <br></br>
                {this.state.questions.map((question, index) => 
                    <div key={index} className='faq-questions'>
                        <p className="question">{question.report}</p>
                        <p className="answer">Answer: {question.answer}</p>
                    </div>
                )}
            </div>
        );
    }
};

export default FAQ;