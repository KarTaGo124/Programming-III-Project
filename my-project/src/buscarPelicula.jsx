import React, { useState } from 'react';
import axios from 'axios';

const MovieSearch = () => {
    const [username, setUsername] = useState('');
    const [movies, setMovies] = useState([]);
    const [error, setError] = useState(null);
    const [loadCount, setLoadCount] = useState("5");

    const handleSearch = async (count) => {
        try {console.log("buscar peliculas",count);
            const response = await axios.post('http://localhost:8080/api/movies', {
                    username,
                    count
                });
            setMovies(response.data);
        } catch (error) {
            setError('Error fetching movies. Please try again.');
        }
    };

    const loadMore = () => {
        setLoadCount(""+(parseInt(loadCount) + 5));
        handleSearch(""+(parseInt(loadCount) + 5));
    };

    const handleInitialSearch = () => {
        setLoadCount("5");
        handleSearch("5");
    };

    return (
        <div>
            <h1>Movie Search</h1>
            <input
                type="text"
                value={username}
                onChange={(e) => setUsername(e.target.value)}
                placeholder="Enter username"
            />
            <button onClick={handleInitialSearch}>Search</button>
            {error && <p>{error}</p>}
            <ul>
                {movies.map((movie) => (
                    <li key={movie.id}>
                        <h3>{movie.title}</h3>
                    </li>
                ))}
            </ul>
            {movies.length > 0 && (
                <button onClick={loadMore}>Load More</button>
            )}
        </div>
    );
};

export default MovieSearch;
