import * as api from './data-api'
import Immutable from 'immutable'
import Papa from 'papaparse'

const LOAD_DATA = 'LOAD_DATA'
const LOAD_DATA_DONE = 'LOAD_DATA_DONE'
const LOAD_DATA_ERROR = 'LOAD_DATA_ERROR'
const LOAD_CATEGORIES = 'LOAD_CATEGORIES'
const LOAD_CATEGORIES_DONE = 'LOAD_CATEGORIES_DONE'
const LOAD_CATEGORIES_ERROR = 'LOAD_CATEGORIES_ERROR'

const SET_FILTER = 'SET_FILTER'


const LOAD_AMP_SETTINGS = 'LOAD_AMP_SETTINGS'
const LOAD_AMP_SETTINGS_DONE = 'LOAD_AMP_SETTINGS_DONE'
const LOAD_AMP_SETTINGS_ERROR = 'LOAD_AMP_SETTINGS_ERROR'


const initialState = Immutable.Map({ mode: 'info' })


export const setFilter = (type, value) => (dispatch) => {

  dispatch({ type: SET_FILTER, param: type, value })

}


export const getCategories = () => (dispatch) => {
  dispatch({
    type: LOAD_CATEGORIES
  })
  api.getCategories().then(data => {
    dispatch({
      type: LOAD_CATEGORIES_DONE,
      data
    })
  }).catch(error => {
    dispatch({
      type: LOAD_CATEGORIES_ERROR,
      error
    })
  })
}

export const setData = ({ csv, store, params }) => (dispatch, getState) => {
  const filters = getState().get('data').getIn(['filters'])
  if (filters) {
    params = { ...params, ...filters.toJS() }
  }

  const data = Papa.parse(csv, { header: true });
  dispatch({ type: LOAD_DATA_DONE, store, data })

}
export const loadSearchData = ({ filters, keyword, page, pageSize, store, currency }) => (dispatch, getState) => {
  debugger;
  dispatch({ type: LOAD_DATA, store })
  api.searchActivities(filters, keyword, page, pageSize, currency)
    .then(data => dispatch({ type: LOAD_DATA_DONE, store, data }))
    .catch(error => dispatch({ type: LOAD_DATA_ERROR, store, error }))
}
export const loadFilters = ({ filterArray, store }) => (dispatch, getState) => {
  filterArray.forEach(filter => {
    const newStore = store + filter;
    dispatch({ type: LOAD_DATA, store: newStore })
    api.loadAmpFilters(filter)
      .then(data => dispatch({ type: LOAD_DATA_DONE, store: newStore, data }))
      .catch(error => dispatch({ type: LOAD_DATA_ERROR, store: newStore, error }))

  })

}
export const getData = ({ app, source, store, params, measure, dateFilter }) => (dispatch, getState) => {
  const filters = getState().get('data').getIn(['filters'])
  if (filters) {
    params = { ...params, ...filters.toJS() }
  }
  dispatch({ type: LOAD_DATA, params, store })
  api.getData(source, params, app, measure, dateFilter)
    .then(data => dispatch({ type: LOAD_DATA_DONE, store, data }))
    .catch(error => dispatch({ type: LOAD_DATA_ERROR, store, error }))
}


export const loadAmpSettings = () => (dispatch) => {
  dispatch({ type: LOAD_AMP_SETTINGS })
  return api.loadAMpSettings()
    .then(data => {
      return dispatch({ type: LOAD_AMP_SETTINGS_DONE, data: data });
    })
    .catch(error => {
      return dispatch({ type: LOAD_AMP_SETTINGS_ERROR, error });
    })
}

export default (state = initialState, action) => {
  switch (action.type) {
    case LOAD_AMP_SETTINGS: {
      const store = ['amp-settings'];
      return state.deleteIn([...store, 'error']).setIn(['amp-settings', 'loading'], true)
    }

    case LOAD_AMP_SETTINGS_ERROR: {
      const store = ['amp-settings'];

      return state
        .setIn([...store, 'loading'], false)
        .setIn(['amp-settings', 'error'], action.error)
    }
    case LOAD_AMP_SETTINGS_DONE: {
      const store = ['amp-settings'];

      return state
        .setIn([...store, 'loading'], false)
        .deleteIn([...store, 'error'])
        .setIn([...store, 'data'], action.data)
    }
    case LOAD_DATA: {
      const { store } = action

      return state.deleteIn([...store, 'error']).setIn([...store, 'loading'], true)
    }
    case LOAD_DATA_ERROR: {
      const { error, store } = action
      return state
        .setIn([...store, 'loading'], false)
        .setIn([...store, 'error'], error)
    }
    case LOAD_DATA_DONE: {
      const { data, store } = action

      return state
        .setIn([...store, 'loading'], false)
        .deleteIn([...store, 'error'])
        .setIn([...store, 'data'], data)
    }


    case LOAD_CATEGORIES:
      return state
    case LOAD_CATEGORIES_DONE:
      const { data } = action

      return state.setIn(['categories'], Immutable.fromJS(data))

    case LOAD_CATEGORIES_ERROR:
      return state
    case SET_FILTER: {
      const { param, value } = action
      if (value.length === 0) {
        return state.deleteIn(['filters', param], value)
      }
      return state.setIn(['filters', param], value)
    }

    default:
      return state
  }
}
