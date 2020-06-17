import React from 'react';
import './App.css';
import {BrowserRouter, Switch, Route} from 'react-router-dom';
import Register from './Components/Register.js';
import Login from './Components/Login.js'
import ArtistsList from './Components/ArtistsList.js'
import SongsList from './Components/SongsList.js'
import Lyrics from './Components/Lyrics';
import AddSong from './Components/AddSong';
import AddArtist from './Components/AddArtist';
import ArtistSongs from './Components/ArtistSongs';
import EditSong from './Components/EditSong';
import 'bootstrap/dist/css/bootstrap.min.css';
import TempSongs from './Components/TempSongs';
import TempLyrics from './Components/TempLyrics';
import TempArtists from './Components/TempArtists';
import RegisterRequests from './Components/RegisterRequests';
import Ask from './Components/Ask';
import Menu from './Components/Menu'
import FAQ from './Components/FAQ';
import Questions from './Components/Questions';
import Search from './Components/Search'

function clearStorage() {
	localStorage.clear('token');
	localStorage.clear('userRole');
	localStorage.clear('username');
	localStorage.clear('email')
};

function App() {

	return (
		<div className='full-width-container'>
			<BrowserRouter className='full-width-container' basename="/">
				<Switch>
					<Route exact path={"/"}>
						<Menu/>
					</Route>
					<Route path="/register">
						<Register/>
					</Route>
					<Route path="/login">
						<Login/>
					</Route>
					<Route path="/Artists">
						<ArtistsList/>
					</Route>
					<Route path="/Songs">
						<SongsList/>
					</Route>
					<Route path="/Lyrics/:artistName/:songName" component={Lyrics}/>
					<Route path="/Lyrics/:artistName" component={ArtistSongs}/>
					<Route path="/EditSong/:songName" component={EditSong}/>
					<Route path="/AddArtist">
						<AddArtist/>
					</Route>
					<Route path="/AddSong">
						<AddSong/>
					</Route>
					<Route path="/AskQuestion">
                    	<Ask/>
                	</Route>
					<Route path="/TempSongs">
						<TempSongs/>
					</Route>
					<Route path="/TempArtists">
						<TempArtists/>
					</Route>
					<Route path="/RegisterRequests">
						<RegisterRequests/>
					</Route>
					<Route path="/Questions">
                    	<Ask/>
                	</Route>
					<Route path="/FAQ">
                    	<FAQ/>
                	</Route>
					<Route path="/AnswerQuestions">
                    	<Questions/>
                	</Route>
					<Route path="/TempLyrics/:artistName/:songName" component={TempLyrics}/>
					<Route path="/Search/:searchValue" component={Search}/>
				</Switch>
			</BrowserRouter>
		</div>
	)
}

export default App;
