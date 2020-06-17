import React from 'react';
import axios from 'axios';
import 'bootstrap/dist/css/bootstrap.min.css';
import Menu from './Menu';
import {Link} from 'react-router-dom';

class TempLyrics extends React.Component {

    constructor(props){
        super(props);
		this.state={
            name: "",
            artistId: "",
            artistName: "",
            genre: "",
            lyrics: "",
            splitLyrics: "",
            value: this.props.match.params.songName,
			song: {}
		}
	}

    componentDidMount() {
        this.fetchData();
    }

    fetchData() {
        axios.get(`http://localhost:3000/api/v1/tempsongs/${this.state.value}`)
		.then((response) => {
            this.setState({song: response.data});
            this.setState({name: response.data.name});
            this.setState({artistId: response.data.artist._id});
            this.setState({artistName: response.data.artist.name});
            this.setState({genre: response.data.genres});
            this.setState({lyrics: response.data.lyrics});
            this.setState(
                {splitLyrics: this.state.lyrics.split('\n').map((i, index) => { return <p key={index}>{i}</p>})
            })
		})
		.catch(error => alert("Error adding songs"));
    }

    deleteSong() {
        let urlDelete =`http://localhost:3000/api/v1/tempsongs/${this.state.name}`
        axios.delete(urlDelete)
        .then((response) => {
            window.location.reload()
        })
        .catch(error => alert("Error deleting songs"));
    }
    
    addSong() {
        const s = {
            name: this.state.name,
            artistName: this.state.artistName,
            genres: this.state.genre,
            lyrics: this.state.lyrics
        }
        axios.get(`http://localhost:3000/api/v1/songs/${this.state.value}`)
		.then((response) => {
            if(response.data != null) {
                if(response.data.artist.name === s.artistName) {
                    axios.put(`http://localhost:3000/api/v1/songs/${s.name}`, s)
                    .then((response) => {
                        //alert(`Song ${this.state.song.name} edited successfully`)
                        this.deleteSong();
                    })
                    .catch(error => alert("Error editing song"));
                
                } else {
                    console.log('ti-ai luat muie')
                    axios.post(`http://localhost:3000/api/v1/songs`, s)
                    .then((response) => {
                        //alert(`Song ${this.state.song.name} added successfully`)
                        this.deleteSong();
                    })
                    .catch(error => alert("Error adding songs"));
                }
            }
		})
        .catch(error => {
            alert("Error getting songs")
        });

    }

    render() {
        return (
            <div className='full-width-container'>
                <Menu></Menu>
                <br></br>
                <div className="lyrics_text">
                    <p className="songName">{this.state.name}</p>
                    <p className="artistName">by {this.state.artistName}</p>
                    <div className="lyr">{this.state.splitLyrics}</div>
                    <br></br>
                    <Link to="/TempSongs">
                        <button className='edit_button' onClick={this.addSong.bind(this)}>Add Song</button>
                    </Link>
                </div>
            </div>
        );
    }
};

export default TempLyrics;