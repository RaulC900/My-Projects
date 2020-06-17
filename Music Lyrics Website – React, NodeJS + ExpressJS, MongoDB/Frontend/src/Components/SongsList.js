import React from "react";
import axios from 'axios';
import Song from './Song';
import 'bootstrap/dist/css/bootstrap.min.css';
import Menu from './Menu';

class SongsList extends React.Component {

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
		const userRole = localStorage.getItem("userRole");
	}

    fetchData() {
        const token = localStorage.getItem("token");
        axios.get('http://localhost:3000/api/v1/songs', {
            headers: {
                Authorization: `Bearer ${token}`
            }
		})
		.then((response) => {
			this.setState({songs: response.data});
		})
		.catch(error => alert("Error adding songs"));
	}
	
	fetchArtists() {
        const token = localStorage.getItem("token");
        axios.get('http://localhost:3000/api/v1/artists', {
            headers: {
                Authorization: `Bearer ${token}`
            }
		})
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
				<div className="cols">
                    <p className="two_cols">
						{this.state.songs.map((song, index) => <Song key={index} data={song}/>)}
					</p>
				</div>
				<br/>
			</div>
		);
	}
    
};
//<input type="text" id="lyrics" name="lyrics" placeholder="Lyrics"></input>
//<input type="text" id="genres" name="genres" placeholder="Genres"/>
export default SongsList;

//pt modify, fac un text area in care am song.lyrics. Cand modific o sa am onChange: lyrics = lyrics modif