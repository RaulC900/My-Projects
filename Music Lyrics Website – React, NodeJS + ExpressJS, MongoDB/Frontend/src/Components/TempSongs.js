import React from "react";
import axios from 'axios';
import 'bootstrap/dist/css/bootstrap.min.css';
import Menu from './Menu';
import {Link} from 'react-router-dom';

class TempSongs extends React.Component {

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
        axios.get('http://localhost:3000/api/v1/tempsongs')
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

	render() {
		return (
			<div className='full-width-container'>
				<Menu></Menu>
				<br></br>
				<br></br>
				<br></br>
				<div className="cols">
					{this.state.songs.map((song, index) => <Link key={index} className="song_link" to={`/TempLyrics/${song.artist.name}/${song.name}`}>{song.name}<br></br></Link>)}
				</div>
				<br/>
			</div>
		);
	}
    
};
export default TempSongs;