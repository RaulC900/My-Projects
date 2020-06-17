import React from "react";
import axios from 'axios';
import 'bootstrap/dist/css/bootstrap.min.css';
import Menu from "./Menu";
var CryptoJS = require("crypto-js");

class AddSong extends React.Component {

    constructor(props){
        super(props);
		this.state={
            songs: [],
            artists: [],
			value: ""
		}
    }

    componentDidMount() {
        this.fetchData();
		this.fetchArtists();
    }
    
    fetchData() {
        axios.get('http://localhost:3000/api/v1/songs')
		.then((response) => {
			this.setState({songs: response.data});
		})
		.catch(error => alert("Error adding songs"));
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
			value: event.target.value
		});
    }

    addNewSong = () => {
        const userRole = localStorage.getItem("userRole");
        if(userRole !== null) {
            var bytes = CryptoJS.AES.decrypt(userRole, process.env.REACT_APP_SECRET_USER_ROLE_KEY);
            var decryptedUserRole = JSON.parse(bytes.toString(CryptoJS.enc.Utf8));
            if(decryptedUserRole == process.env.REACT_APP_ADMIN_ROLE || decryptedUserRole == process.env.REACT_APP_TECH_ROLE || decryptedUserRole == process.env.REACT_APP_USER_ROLE) {
                const song = {
                    name: document.getElementById("name").value,
                    artistName: this.state.value,
                    genres: document.getElementById("genres").value,
                    lyrics: document.getElementById("lyrics").value
                };
                const alreadyExists = this.state.songs.some(existing => (existing.name === song.name && existing.artist.name === song.artistName));
                if(alreadyExists) {
                    alert(`Song ${song.name} by ${song.artistName} already exists !`)
                } else {
                    axios.post('http://localhost:3000/api/v1/tempsongs', song)
                    .then(() => {
                        alert(`Your song addition (${song.name} by ${song.artistName}) will be reviewed soon !`)
                        this.fetchData();
                    }).catch(error => {
                        alert(error)
                    });
                }
            } else {
                alert('You must be logged in to add a song')
            }
        } else {
            alert('You must be logged in to add a song')
        }
    };

    render() {
        return (
            <div className='full-width-container'>
                <Menu></Menu>
                <br></br>
				<fieldset className="fieldset">
                    <legend className='labels'>New song:</legend>
                    <br></br>
                    <label className='labels' htmlFor="name">Song Title: </label>
                    <br></br>
                    <input className='input-box' type="text" id="name" name="name" placeholder="Song Title"/>
                    <br /> <br />
                    <label className='labels' htmlFor="artist">Artist Name: 
                        <br></br>
                        <select className='input-box' defaultValue={this.state.value} value={this.state.value} onChange={this.handleChange}>
                            {this.state.artists.map(artist => (
                                <option key={artist.name} value={artist.name}>
                                    {artist.name}
                                </option>
                            ))}
                        </select>
                    </label>
                    <br /> <br />
                    <p>{this.state.value}</p>
                    <label className='labels' htmlFor="genres">Genres: </label>
                    <br></br>
                    <input className='input-box' type="text" id="genres" name="genres" placeholder="Genres"/>
                    <br /><br />
                    <label className='labels' htmlFor="lyrics">Lyrics: </label>
                    <br></br>
                    <textarea className='input-box' id="lyrics" name="lyrics" rows={25} style={{minWidth: 340}}></textarea>
                    <br></br>
                    <button className='edit_button' onClick={this.addNewSong}>Submit</button>
                </fieldset>
            </div>
        )
    }

}

export default AddSong;