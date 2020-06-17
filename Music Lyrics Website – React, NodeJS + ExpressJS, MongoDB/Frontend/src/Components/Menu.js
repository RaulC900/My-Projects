import React, { useState, useEffect } from 'react';
import {Switch, Route, Link} from 'react-router-dom';
import 'bootstrap/dist/css/bootstrap.min.css';
import Container from 'react-bootstrap/Container'
import Register from './Register.js';
import Login from './Login.js'
import ArtistsList from './ArtistsList.js'
import SongsList from './SongsList.js'
import Lyrics from './Lyrics';
import AddSong from './AddSong';
import AddArtist from './AddArtist';
import Row from 'react-bootstrap/Row';
import TempSongs from './TempSongs';
import TempArtists from './TempArtists';
import RegisterRequests from './RegisterRequests';
import Ask from './Ask';
import FAQ from './FAQ';
import Questions from './Questions';
import Search from './Search'
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome'
import { faSearch } from '@fortawesome/free-solid-svg-icons';

var CryptoJS = require("crypto-js");

function clearStorage() {
    localStorage.clear('token');
    localStorage.clear('userRole');
    localStorage.clear('username');
    localStorage.clear('email');
    window.location.reload();
};

function Menu() {
    const userRole = localStorage.getItem("userRole");
    const [show, setShow] = useState(false);
    const [showTech, setShowTech] = useState(false);
    const [searchValue, setSearchValue] = useState("");

	useEffect(() => {
        if(userRole !== null) {
            var bytes = CryptoJS.AES.decrypt(userRole, process.env.REACT_APP_SECRET_USER_ROLE_KEY);
            var decryptedUserRole = JSON.parse(bytes.toString(CryptoJS.enc.Utf8));
            if(decryptedUserRole == process.env.REACT_APP_ADMIN_ROLE) {
                setShow(true);
            }
            if(decryptedUserRole == process.env.REACT_APP_ADMIN_ROLE || decryptedUserRole == process.env.REACT_APP_TECH_ROLE) {
                setShowTech(true);
            }
        }
    }, []);
    
    const handleChange = (event) => {
        const value = event.target.value;
        setSearchValue(value)
    };

    return(
        <div className='menubar-container'>
            <Container className='menubar'>
                <Switch>
                    <Route>
                        <div class="row">
                            <Link className="menu_links" to="/">Home</Link>
                            <Link className="menu_links" to="/login">Login</Link>
                            <Link className="menu_links" to="/register">Register</Link>
                            <Link className="menu_links" to="/Artists">All Artists</Link>
                            <Link className="menu_links" to="/Songs">All Songs</Link>
                            <Link className="menu_links" to="/AddArtist">Add Artist</Link>
                            <Link className="menu_links" to="/AddSong">Add Song</Link>
                            <Link className="menu_links" to="/Questions">Submit Question</Link>
                            <Link className="menu_links" to="/FAQ">FAQ</Link>
                            <Link to="/" className="menu_links" onClick={clearStorage}>Logout</Link>
                        </div>
                        <div class="row">
                            <span>
                                {show ? <Link className="menu_links" to="/TempSongs">Temp Songs</Link> : null}
                            </span>
                            <span>
                                {show ? <Link className="menu_links" to="/TempArtists">Temp Artists</Link> : null}
                            </span>
                            <span>
                                {show ? <Link className="menu_links" to="/RegisterRequests">Register Requests</Link> : null}
                            </span>
                            <span>
                                {showTech ? <Link className="menu_links" to="/AnswerQuestions">Answer Questions</Link> : null}
                            </span>
                        </div>
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
                    <Route path="/Lyrics/:songName" component={Lyrics}/>
                    <Route path="/AddArtist">
                        <AddArtist/>
                    </Route>
                    <Route path="/AddSong">
                        <AddSong/>
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
                    <Route path="/Search/:searchValue" component={Search}/>
                </Switch>
            </Container>
            <Container>
                <Row className='menubar_row'>
                    <input 
                        className='search-box'
                        type="text"
                        onChange={handleChange}
                        placeholder="Search"
                    />
                    <Link className="menu_links" to={`/Search/${searchValue}`}><FontAwesomeIcon icon={faSearch}/></Link>
                </Row>
            </Container>
        </div>
    )
}

export default Menu;




