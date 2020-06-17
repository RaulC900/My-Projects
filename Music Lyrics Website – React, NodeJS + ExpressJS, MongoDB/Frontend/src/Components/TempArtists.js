import React from 'react';
import axios from 'axios';
import 'bootstrap/dist/css/bootstrap.min.css';
import Menu from './Menu';

class TempArtists extends React.Component {

    constructor(props){
        super(props);
        this.state={ 
            artists: []
        }
    }

    componentDidMount(){
        this.fetchData();
    }

    fetchData() {
        axios.get('http://localhost:3000/api/v1/tempartists')
		.then((response) => {
			this.setState({artists: response.data});
		})
		.catch(error => alert("Error adding artist"));
    }

    deleteArtist = (name) => {
        let urlDelete =`http://localhost:3000/api/v1/tempartists/${name}`
        axios.delete(urlDelete)
        .then((response) => {
            this.fetchData();
        })
        .catch(error => alert("Error deleting artist"));
    }

    addNewArtist = (name) => {
        const artist = {
            name: name
		};
        axios.get(`http://localhost:3000/api/v1/artists/${name}`)
		.then((response) => {
            if(response.data === null){
                axios.post('http://localhost:3000/api/v1/artists', artist)
                .then(() => {
                    this.deleteArtist(name);
                }).catch(error => {
                    alert('Error adding artist')
                });
            } else {

            }
        })
        .catch(error => {
            alert("Error getting artists")
        });
    };

    render() {
		return (
			<div className='full-width-container'>
                <Menu></Menu>
				<br></br>
				<br></br>
				<div className="cols">
                    {this.state.artists.map((artist, index) => 
                        <div key={index}>
                            <span className="temp-artists">{artist.name}</span>
                            <button className='temp-add-artists' onClick={() => this.addNewArtist(artist.name)}>Add Artist</button>
                            <button className='edit_button' onClick={() => this.deleteArtist(artist.name)}>Delete Artist</button>
                        </div>
                    )}
				</div>
				<br/>
			</div>
		);
	}
  }
  
  export default TempArtists;
