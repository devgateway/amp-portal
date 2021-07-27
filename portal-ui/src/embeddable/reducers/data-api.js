import { get, post } from '../../api/commons';

const API_ROOT = process.env.REACT_APP_API_URL;
const FILTERS_API = '/filters'
const TOP_API = '/dashboard/tops';
const GIS_API = '/gis/cluster'
const TOTAL_API = '/public/totalByMeasure'
const COUNT_API = '/public/projectCount'
const TOP_DONORS_API = '/public/donorFunding';
const TOP_PROJECTS_API = '/public/topprojects';
const SEARCH_API = '/public/searchprojects';

const SCORECARD_API = '/scorecard/stats';
const URL_TAXONOMY = API_ROOT + '/categories'
const AMP_SETTINGS_API = `${API_ROOT}/amp/settings`
const filters_data = {
    "filters": { "date": { "start": "2000-01-01", "end": "2030-12-31" } },
    "include-location-children": true,
    "settings": { "currency-code": "USD", "funding-type": "Actual Commitments" }
  }
;
const filters_dataFT = {
  "filters": { "date": { "start": "2010-01-01", "end": "2030-12-31" } },
  "include-location-children": true,
  "settings": { "currency-code": "USD", "funding-type": "Actual Commitments" }
};

const filters_GIS = {
  "filters": {
    "date": { "start": "2000-01-01", "end": "2020-12-31" },
    "adminLevel": "Administrative Level 1"
  }, "include-location-children": true, "settings": {}
};
const topDonorsFilters = {
  "reportType": "D",
  "projectType": [
    "A"
  ],
  "settings": {
    "calendar-id": "4",
    "currency-code": "USD"
  },
  "filters": {
    "date": {
      "start": "2000-01-01",
      "end": "2030-01-01"
    }
  }
};

const searchApiJson = {
  "page": 1,
  "recordsPerPage": 10,
  "add_columns": [
    "Activity Id",
    "Actual Start Date",
    "Primary Sector",
    "Project Title"
  ],
  "add_measures": [
    "Actual Commitments",
    "Actual Disbursements"
  ],
  "rowTotals": true,
  "show_empty_rows": true,
  "name": "Activity search"
};

//TODO settings came from settings
export const getCategories = (params) => {
  return get(URL_TAXONOMY, params)
}
export const loadAMpSettings = () => {
  return get(AMP_SETTINGS_API);
}
export const loadAmpFilters = (filterName) => {
  const url = API_ROOT + FILTERS_API + '/' + filterName;
  return get(url);
}
export const searchActivities = (filters, keyword, page, pageSize) => {
  const url = API_ROOT + SEARCH_API;
  searchApiJson.page = page;
  searchApiJson.recordsPerPage = pageSize;
  searchApiJson.filters = {};
  if (keyword) {
    searchApiJson.filters.keyword = keyword;
  }
  return post(url, searchApiJson);
};

export const getData = (path, params, app, measure, dateFilter) => {
  const route = path.split('/');
  let url;
  let isPost = true;
  let filters = filters_data;
  switch (app) {
    case 'top':
      url = API_ROOT + TOP_API + '/' + route[0] + '?limit=' + route[1];
      break
    case 'funding':
      url = API_ROOT + "/dashboard/" + route[0];
      filters = filters_dataFT;
      break;
    case 'donorScoreCard':
      url = API_ROOT + SCORECARD_API;
      isPost = false;
      break;
    case 'map':
      url = API_ROOT + GIS_API;
      filters = filters_GIS;
      if (route.length > 0) {
        filters.filters.adminLevel = route[0];
      }
      break;
    case 'totalWidget':
      if (measure === 'Total Activities') {
        url = API_ROOT + COUNT_API;

      } else {
        url = API_ROOT + TOTAL_API;
      }
      filters = filters_data
      break;
    case "topLists":
      if (route[0] === "topDonors") {
        url = `${API_ROOT}${TOP_DONORS_API}`;
      } else {
        url = `${API_ROOT}${TOP_PROJECTS_API}`;
      }
      url += `?count=${route[1] === 'top5' ? '5' : 10}`
      url += `&months=${route[2]}&fundingType=${measure === 'Actual Commitments' ? '1' : '2'}`;
      url += `&showDonorGroup=${route[4]}`
      if (route[0] === 'topUpdatedProjects') {
        url += `&lastUpdated=true`

      }
      topDonorsFilters.settings['currency-code'] = route[3];
      measure = null;
      filters = topDonorsFilters;
      break;
    case "activitiesSearch":
      url = API_ROOT + SEARCH_API;
      filters = searchApiJson;
      break
    default:
      url = API_ROOT + "/dashboard/ftype";
      break;
  }
  if (dateFilter && filters) {
    if (dateFilter.from) {
      filters.filters.date.start = `${dateFilter.from}-01-01`;
    }
    if (dateFilter.to) {
      filters.filters.date.end = `${dateFilter.to}-12-31`;
    }
  }
  if (filters) {
    if (measure) {
      filters.settings['funding-type'] = measure;
    }
  }

  if (isPost) {
    return post(url, filters);
  } else {
    return get(url);
  }
}

