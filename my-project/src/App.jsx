import React, { useState } from 'react';
import axios from 'axios';

const App = () => {
    const [busqueda, setBusqueda] = useState('');
    const [resultados, setResultados] = useState([]);
    const buscarPeliculas = async () => {
        try {
            const respuesta = await axios.get('http://localhost:8080/api/movies', {
        busqueda
      });
            setResultados(respuesta.data.resultados);
        } catch (error) {
            console.error('Error al buscar películas:', error);
        }
    };

    return (
        <div>
            <input
                type="text"
                value={busqueda}
                onChange={(e) => setBusqueda(e.target.value)}
                placeholder="Buscar películas..."
            />
            <button onClick={buscarPeliculas}>Buscar</button>
            
        </div>
    );
};

export default App;