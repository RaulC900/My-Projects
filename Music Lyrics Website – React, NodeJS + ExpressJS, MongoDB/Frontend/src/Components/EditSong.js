import React from 'react';
import axios from 'axios';
import 'bootstrap/dist/css/bootstrap.min.css';
import Menu from './Menu';
import {Switch, Route, Link} from 'react-router-dom';
var CryptoJS = require("crypto-js");

class EditSong extends React.Component {

    constructor(props){
        super(props);
        this.state={
            value: this.props.match.params.songName,
            song: {},
            artist: "",
            artists: [],
            selectedArtist: "",
            modifiedName: "",
            modifiedGenre: "",
            modifiedLyrics: ""
        }
    }

    componentDidMount() {
        this.fetchSong();
        this.fetchArtists();
    }

    fetchSong() {
        axios.get(`http://localhost:3000/api/v1/songs/${this.state.value}`)
		.then((response) => {
            this.setState({song: response.data});
            this.setState({artist: response.data.artist.name});
            this.setState({selectedArtist: response.data.artist.name});
            this.setState({modifiedName: response.data.name});
            this.setState({modifiedGenre: response.data.genres});
            this.setState({modifiedLyrics: response.data.lyrics});
		})
		.catch(error => alert("Error adding song"));
    }

    fetchArtists() {
        axios.get('http://localhost:3000/api/v1/artists')
		.then((response) => {
			this.setState({artists: response.data});
		})
		.catch(error => alert("Error adding artists"));
	}
    
    handleChange = (event) => {
        this.setState({
			selectedArtist: event.target.value
		});
    }

    changeName = (event) => {
        this.setState({
			modifiedName: event.target.value
		});
    }

    changeGenre = (event) => {
        this.setState({
			modifiedGenre: event.target.value
		});
    }

    changeLyrics = (event) => {
        this.setState({
			modifiedLyrics: event.target.value
		});
    }

    modify = () => {
        const userRole = localStorage.getItem("userRole");
        if(userRole !== null) {
            var bytes = CryptoJS.AES.decrypt(userRole, process.env.REACT_APP_SECRET_USER_ROLE_KEY);
            var decryptedUserRole = JSON.parse(bytes.toString(CryptoJS.enc.Utf8));
            if(decryptedUserRole == process.env.REACT_APP_ADMIN_ROLE || decryptedUserRole == process.env.REACT_APP_TECH_ROLE || decryptedUserRole == process.env.REACT_APP_USER_ROLE) {
                const song = {
                    name: this.state.modifiedName,
                    artistName: this.state.selectedArtist,
                    genres: this.state.modifiedGenre,
                    lyrics: this.state.modifiedLyrics
                };
                axios.post(`http://localhost:3000/api/v1/tempsongs`, song)
                .then(() => {
                    alert(`Your modifications review for song ${this.state.song.name} will be reviewed soon !`)
                    this.fetchSong();
                }).catch(error => {
                    alert(error)
                });
            } else {
                alert('You must be logged in to edit a song')
            }
        } else {
            alert('You must be logged in to edit a song')
        }
    };
    
    render() {
        return (
            <div className='full-width-container'>
                <Menu></Menu>
                <br></br>
                <div className="lyrics_text">
                    <p className="songName">{this.state.song.name}</p>
                    <br></br>
                    <p className="artistName">by {this.state.artist}</p>
                    <br></br>
                </div>
                <br></br>
                <fieldset className="fieldset">
                    <legend className='labels'>Edit Lyrics: </legend>
                    <br></br>
                    <label className='labels' htmlFor="name">Song Title: </label>
                    <br></br>
                    <input className='input-box' type="text" id="name" name="name" defaultValue={this.state.modifiedName} onChange={this.changeName}/>
                    <br /> <br />
                    <label className='labels' htmlFor="artist">Artist Name: 
                        <br></br>
                        <select className='input-box' value={this.state.selectedArtist} onChange={this.handleChange}>
                            {this.state.artists.map((artist, index) => (
                                <option key={index} value={artist.name}>
                                    {artist.name}
                                </option>
                            ))}
                        </select>
                    </label>
                    <br /> <br />
                    <label className='labels' htmlFor="genres">Genres: </label>
                    <br></br>
                    <input className='input-box' type="text" id="genres" name="genres" defaultValue={this.state.modifiedGenre} onChange={this.changeGenre}/>
                    <br /><br />
                    <label className='labels' htmlFor="lyrics">Lyrics: </label>
                    <br></br>
                    <textarea className='input-box' id="lyrics" name="lyrics" rows={25} 
                                style={{minWidth: 340}} defaultValue={this.state.modifiedLyrics} onChange={this.changeLyrics}></textarea>
                    <br></br>
                    <Switch>
                        <Route>
                            <Link to={`/Lyrics/${this.state.selectedArtist}`}>
                                <button className='edit_button' onClick={this.modify}>Submit Changes</button>
                            </Link>
                        </Route>
                    </Switch>
                </fieldset>
            </div>
        );
    }
}

export default EditSong;