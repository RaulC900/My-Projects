import React from 'react';
import axios from 'axios';
import 'bootstrap/dist/css/bootstrap.min.css';
import Menu from './Menu';
import {Switch, Route, Link} from 'react-router-dom';

class Search extends React.Component {

    constructor(props){
        super(props);
        this.state={
            value: this.props.match.params.searchValue,
            songs: [],
            artists: []
        }
    }

    componentDidMount() {
        this.fetchSongs();
        this.fetchArtists();
    }

    fetchSongs() {
        axios.get(`http://localhost:3000/api/v1/songs/search/${this.state.value}`)
		.then((response) => {
            if(response.data != null) {
                let aux = this.state.songs;
                aux.push(response.data)
                this.setState({songs: aux});
            }
		})
        .catch(error => alert("Error adding songs"));
        
        axios.get(`http://localhost:3000/api/v1/songs/searchLowercase/${this.state.value}`)
		.then((response) => {
            if(response.data != null) {
                let aux1 = this.state.songs;
                aux1.push(response.data)
                this.setState({songs: aux1});
            }
		})
		.catch(error => alert("Error adding songs"));
    }

    fetchArtists() {
        axios.get(`http://localhost:3000/api/v1/artists/search/${this.state.value}`)
		.then((response) => {
            if(response.data != null) {
                let aux = this.state.artists;
                aux.push(response.data)
                this.setState({artists: aux});
            }
		})
        .catch(error => alert("Error adding artists"));

        axios.get(`http://localhost:3000/api/v1/artists/searchLowercase/${this.state.value}`)
		.then((response) => {
            if(response.data != null) {
                let aux1 = this.state.artists;
                aux1.push(response.data)
                this.setState({artists: aux1});
            }
		})
		.catch(error => alert("Error adding artists"));
    }

    render() {
        return (
            <div className='full-width-container'>
                <Menu></Menu>
                <br></br>
                <br></br>
                <div className="cols">
                    <label className='labels1' htmlFor="songs">Songs</label>
                    <br></br>
                    {this.state.songs != null
                        ? this.state.songs.map(song => 
                            <Link className="song_link" to={`/Lyrics/${song.artist.name}/${song.name}`}>{song.name}<br></br></Link>) 
                        : <div>Haven't found songs</div>}
                    <br></br>
                    <label className='labels1' htmlFor="artists">Artists</label>
                    <br></br>
                    {this.state.artists != null
                        ? this.state.artists.map(artist => 
                            <Link className="song_link" to={`/Lyrics/${artist.name}`}>{artist.name}<br></br></Link>) 
                        : <div>Haven't found artists</div>}
                </div>
            </div>
        );
    }

}

export default Search;