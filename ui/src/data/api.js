import { get, post } from '../api/commons'

const API_ROOT = process.env.REACT_APP_API_URL;
const TOP_API = '/dashboard/tops';
const SCORECARD_API= '/scorecard/stats';
const URL_TAXONOMY = API_ROOT + '/categories'
const URL_STATS = API_ROOT;//+ '/stats'
const filters_data = {
  "filters": { "date": { "start": "2000-01-01", "end": "2030-12-31" } },
  "include-location-children": true,
  "settings": { "currency-code": "USD", "funding-type": "Actual Commitments" }
};
const filters_dataFT = {
  "filters": { "date": { "start": "2010-01-01", "end": "2030-12-31" } },
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

export const getData = (path, params, app, measure, dateFilter) => {
  const route = path.split('/');
  let url;
  let isPost = true;
  let filters = filters_data;
  if (app === 'top') {
    url = API_ROOT + TOP_API + '/' + route[0] + '?limit=' + route[1];
  } else {
    if (app === 'funding') {
      url = API_ROOT + "/" + route[0];
      filters = filters_dataFT;
    } else if (app === 'donorScoreCard') {
      url = API_ROOT + SCORECARD_API;
      isPost = false;
    } else {
      url = API_ROOT + "/ftype";
    }
  }
  if (dateFilter) {
    if (dateFilter.from) {
      filters.filters.date.start = `${dateFilter.from}-01-01`;
    }
    if (dateFilter.to) {
      filters.filters.date.end = `${dateFilter.to}-12-31`;
    }
  }
  if (measure) {
    filters.settings['funding-type'] = measure;
  }

  if(isPost){
  return post(url, filters);
  }else{
    return get(url);
  }
}

