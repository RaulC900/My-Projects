import React from 'react';
import {Switch, Route, Link} from 'react-router-dom';

const Song = props => {
    let a = '/Lyrics/' + props.data.artist.name + '/' + props.data.name
    return (
        <Switch>
            <Route>
                <Link className="song_link" to={a}>{props.data.name}<br></br></Link>
            </Route>
        </Switch>
    );
};

export default Song;
//as putea sa pun sortare dupa nume