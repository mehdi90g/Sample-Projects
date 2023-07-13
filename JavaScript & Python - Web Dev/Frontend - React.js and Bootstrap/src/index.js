import React from 'react';
import ReactDOM from 'react-dom';
import App from './App';

import 'bootstrap/dist/css/bootstrap.min.css';
import 'bootstrap/dist/js/bootstrap.bundle.min.js';

import {
  BrowserRouter,
  Routes,
  Route
} from "react-router-dom";

import {Dashboard} from "./dashboard/Dashboard";
import {Error} from "./error/Error";


ReactDOM.render(
  <React.StrictMode>

    <BrowserRouter>
      <Routes>
        <Route path="/" element={<App />} />
        <Route path="dashboard" element={<Dashboard />} />
        <Route path="*" element={<Error />} />
      </Routes>
    </BrowserRouter>,

  </React.StrictMode>,
  document.getElementById('root')
);

