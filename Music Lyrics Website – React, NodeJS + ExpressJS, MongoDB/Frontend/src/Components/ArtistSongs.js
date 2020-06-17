import React from 'react';
import axios from 'axios';
import {Switch, Route, Link} from 'react-router-dom';
import 'bootstrap/dist/css/bootstrap.min.css';
import Menu from './Menu';

class ArtistSongs extends React.Component {

    constructor(props){
        super(props);
		this.state={
            value: this.props.match.params.artistName,
			songs: []
		}
	}

    componentDidMount() {
        this.fetchData();
    }

    fetchData() {
        axios.get(`http://localhost:3000/api/v1/songs/artists/${this.state.value}`)
		.then((response) => {
            this.setState({songs: response.data});
		})
		.catch(error => alert("Error adding songs"));
	}

    render() {
        return (
            <div className='full-width-container'>
                <Menu></Menu>
                <br></br>
                <div className="cols">
                    <p className="two_cols">
                        <Switch>
                            <Route>
                                {this.state.songs.map((song, index) => <Link key={index} to={`/Lyrics/${song.artist.name}/${song.name}`} className="song_link">{song.name}<br></br></Link>)}
                            </Route>
                        </Switch>
                    </p>
                </div>
            </div>
        );
    }
};

export default ArtistSongs;