import React from 'react';
import axios from 'axios';
import 'bootstrap/dist/css/bootstrap.min.css';
import Menu from './Menu';
import {Switch, Route, Link} from 'react-router-dom';
var CryptoJS = require("crypto-js");

class Lyrics extends React.Component {

    constructor(props){
        super(props);
		this.state={
            name: "",
            artist: "",
            lyrics: "",
            splitLyrics: "",
            value: this.props.match.params.songName,
            song: {},
            comments: [],
            samples: [],
            showDel: false
		}
	}

    componentDidMount() {
        this.fetchData();
        this.fetchComments();
        this.fetchSamples();
        const userRole = localStorage.getItem("userRole");
        if(userRole !== null) {
            var bytes = CryptoJS.AES.decrypt(userRole, process.env.REACT_APP_SECRET_USER_ROLE_KEY);
            var decryptedUserRole = JSON.parse(bytes.toString(CryptoJS.enc.Utf8));
            if(decryptedUserRole == process.env.REACT_APP_ADMIN_ROLE) {
                this.setState({showDel: true})
            }
        }
    }

    fetchData() {
        axios.get(`http://localhost:3000/api/v1/songs/${this.state.value}`)
		.then((response) => {
            this.setState({song: response.data});
            this.setState({name: response.data.name});
            this.setState({artist: response.data.artist.name});
            this.setState({lyrics: response.data.lyrics});
            this.setState(
                {splitLyrics: this.state.lyrics.split('\n').map((i, index) => { return <p key={index}>{i}</p>})
            })
		})
		.catch(error => alert("Error adding songs"));
    }

    fetchComments() {
        axios.get(`http://localhost:3000/api/v1/songs/comments/${this.state.value}`)
		.then((response) => {
            if(response.data === 'No comments') {
                let msg = 'No comments'
            } else {
                this.setState({comments: response.data});
            }
		})
		.catch(error => alert("Error fetching comments"));
    }

    fetchSamples() {
        axios.get(`http://localhost:3000/api/v1/songs/samples/${this.state.value}`)
		.then((response) => {
            if(response.data === 'No samples') {
                let msg = 'No samples'
            } else {
                this.setState({samples: response.data});
            }
		})
		.catch(error => alert("Error fetching samples"));
    }

    addCommentToSong = (comm) => {
        const obj = {
            comm: comm
        }
        axios.put(`http://localhost:3000/api/v1/songs/comments/${this.state.value}`, obj)
        .then((response) => {
            alert('Comment added')
            this.fetchComments()
        })
        .catch(error => alert("Error adding comment"));
    }
    
    addComment() {
        const userRole = localStorage.getItem("userRole");
        const username = localStorage.getItem("username");
        if(userRole !== null) {
            var bytes = CryptoJS.AES.decrypt(userRole, process.env.REACT_APP_SECRET_USER_ROLE_KEY);
            var decryptedUserRole = JSON.parse(bytes.toString(CryptoJS.enc.Utf8));
            if(decryptedUserRole == process.env.REACT_APP_ADMIN_ROLE || decryptedUserRole == process.env.REACT_APP_TECH_ROLE || decryptedUserRole == process.env.REACT_APP_USER_ROLE) {
                const comm = {
                    authorUsername: username,
                    comment: document.getElementById("commentText").value
                }
                const token = localStorage.getItem("token");
                axios.post(`http://localhost:3000/api/v1/comments`, comm, {
                    headers: {
                        Authorization: `Bearer ${token}`
                    }
                })
                .then((response) => {
                    const comm = response.data
                    this.addCommentToSong(comm)
                })
                .catch(error => alert("Error adding comment"));
            } else {
                alert('You must be logged in to add a comment')
            }
        } else {
            alert('You must be logged in to add a comment')
        }
    }

    addSampleToSong = (samp) => {
        const obj = {
            samp: samp
        }
        axios.put(`http://localhost:3000/api/v1/songs/samples/${this.state.value}`, obj)
        .then((response) => {
            alert('Sample added')
            this.fetchSamples()
        })
        .catch(error => alert("Error adding sample"));
    }
    
    addSample() {
        const userRole = localStorage.getItem("userRole");
        const username = localStorage.getItem("username");
        if(userRole !== null) {
            var bytes = CryptoJS.AES.decrypt(userRole, process.env.REACT_APP_SECRET_USER_ROLE_KEY);
            var decryptedUserRole = JSON.parse(bytes.toString(CryptoJS.enc.Utf8));
            if(decryptedUserRole == process.env.REACT_APP_ADMIN_ROLE || decryptedUserRole == process.env.REACT_APP_TECH_ROLE || decryptedUserRole == process.env.REACT_APP_USER_ROLE) {
                const comm = {
                    authorUsername: username,
                    sample: document.getElementById("sampleText").value,
                    videoLink: document.getElementById("videoLink").value
                }
                const token = localStorage.getItem("token");
                axios.post(`http://localhost:3000/api/v1/samples`, comm)
                .then((response) => {
                    const samp = response.data
                    this.addSampleToSong(samp)
                })
                .catch(error => alert("Error adding sample"));
            } else {
                alert('You must be logged in to add a sample')
            }
        } else {
            alert('You must be logged in to add a sample')
        }
    }

    deleteComment = (id) => {
        axios.delete(`http://localhost:3000/api/v1/songs/comments/${this.state.value}/${id}`)
        .then((response) => {
            alert("Comment deleted!");
            this.fetchComments()
		})
        .catch(error => alert("Error deleting commment"));
    }

    render() {
        return (
            <div className='full-width-container'>
                <Menu></Menu>
                <br></br>
                <div className="lyrics_text">
                    <p className="songName">{this.state.name}</p>
                    <p className="artistName">by {this.state.artist}</p>
                    <div className="lyr">{this.state.splitLyrics}</div>
                    <br></br>
                    <Switch>
                        <Route>
                            <Link to={`/EditSong/${this.state.name}`}>
                                <button className='edit_button'>Edit Song</button>
                            </Link>
                        </Route>
                    </Switch>
                    <br></br>
                    <label className='labels' htmlFor="commentText">Your comment: </label>
                    <br></br>
                    <textarea className='input-box' id="commentText" name="commentText" rows={3} style={{minWidth: 340}}></textarea>
                    <br></br>
                    <br></br>
                    <button className='edit_button' onClick={this.addComment.bind(this)}>Add Comment</button>
                    <br></br>
                    <label className='labels' htmlFor="sampleText">Your sample: </label>
                    <br></br>
                    <textarea placeholder="Sample Name" className='input-box' id="sampleText" name="sampleText" rows={1} style={{minWidth: 340}}></textarea>
                    <br></br>
                    <textarea placeholder="Sample Video Link" className='input-box' id="videoLink" name="videoLink" rows={1} style={{minWidth: 340}}></textarea>
                    <br></br>
                    <br></br>
                    <button className='edit_button' onClick={this.addSample.bind(this)}>Add Sample</button>
                    <br></br>
                    <div className='comments-text'>
                        <label className='labels1' htmlFor="comment-area">Samples</label>
                    </div>
                    <div className='line'></div>
                    {this.state.samples.map((sample, index) => 
                        <div>
                            <div key={index} className='samp0'>
                                <p className="samp1">{sample.authorUsername}</p>
                                <a className="samp3" href={sample.videoLink} target="_blank">{sample.sample}</a>
                            </div>
                        </div>
                    )}
                    <br></br>
                    <br></br>
                    <div className='comments-text'>
                        <label className='labels1' htmlFor="comment-area">Comments</label>
                    </div>
                    <div className='line'></div>
                    {this.state.comments.map((comment, index) => 
                        <div>
                            <div key={index} className='faq-questions'>
                                <p className="authorEmail1">{comment.authorUsername}</p>
                                <p className="answer1">{comment.comment}</p>
                            </div>
                            {this.state.showDel ? <button className='temp-add-artists' onClick={() => this.deleteComment(comment._id)}>Delete</button> : null}
                        </div>
                    )}
                </div>
            </div>
        );
    }
};

export default Lyrics;