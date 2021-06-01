import { get, post } from '../api/commons'

const API_ROOT = process.env.REACT_APP_API_URL;
const TOP_API = '/tops';
const URL_TAXONOMY = API_ROOT + '/categories'
const URL_STATS = API_ROOT;//+ '/stats'
const filters_data = {
  "filters": { "date": { "start": "2000-01-01", "end": "2030-12-31" } },
  "include-location-children": true,
  "settings": { "currency-code": "USD", "funding-type": "Actual Commitments" }
};

//TODO settings came from settings

function queryParams(params) {
  return Object.keys(params)
    .map(k => encodeURIComponent(k) + '=' + encodeURIComponent(params[k]))
    .join('&')
}

export const getCategories = (params) => {
  return get(URL_TAXONOMY, params)
}
export const getData = (path, params) => {
  const route = path.split('/');
  const url = API_ROOT + TOP_API + '/' + route[0] + '?limit=' + route[1];
  return post(url, filters_data);
}

