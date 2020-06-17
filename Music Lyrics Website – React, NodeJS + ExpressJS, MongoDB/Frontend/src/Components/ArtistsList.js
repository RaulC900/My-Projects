import React from 'react';
import axios from 'axios';
import Artist from './Artist'
import 'bootstrap/dist/css/bootstrap.min.css';
import Menu from './Menu';

class ArtistsList extends React.Component {

    constructor(props){
        super(props);
        this.state={ artists: [] }
    }

    componentDidMount(){
        this.fetchData();
    }

    fetchData() {
        axios.get('http://localhost:3000/api/v1/artists')
		.then((response) => {
			this.setState({artists: response.data});
		})
		.catch(error => alert("Error adding artist"));
    }

    addNewArtist = () => {
        const artist = {
            name: document.getElementById("name").value
		};
        axios.post('http://localhost:3000/api/v1/artists', artist)
        .then(() => {
            this.fetchData();
        }).catch(error => {
            alert(error)
        });
    };

    deleteArtist = (id) => {
        axios.delete(`http://localhost:3000/api/v1/artists/${id}`)
        .then(() => {
            this.fetchData();
        }).catch(error => {
            alert(error)
        });
    };

    render() {
		return (
			<div className='full-width-container'>
                <Menu></Menu>
				<div className="cols">
                    <p className="two_cols">
						{this.state.artists.map(artist => <Artist data={artist}/>)}
                    </p>
				</div>
				<br/>
			</div>
		);
	}
  }
  
  export default ArtistsList;
