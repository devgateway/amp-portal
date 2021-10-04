import React from 'react'
import { connect } from 'react-redux'
import { injectIntl } from 'react-intl';
import DataContext from './DataContext'
import { Container, Loader, Segment } from "semantic-ui-react";
import { getData, loadFilters, setData } from "../reducers/data";

class DataProvider extends React.Component {

  componentDidMount() {
    const { source, store, app, measure, dateFilter, params, csv, locale, keyword } = this.props
    if (app === "csv") {
      this.props.onSetData({ app, csv, store, params })
    } else {
      if (app === 'activitiesSearch') {
        const filterArray = ['locations', 'sectors', 'organizations'];
        this.props.loadFilters_({ filterArray, store, locale });
      }
      this.props.onLoadData({ app, source, store, measure, dateFilter, locale, keyword });
    }

  }

  componentDidUpdate(prevProps, prevState, snapshot) {
    const { filters, app, source, store, params, csv, locale } = this.props

    if (filters !== prevProps.filters || app !== prevProps.app || prevProps.source !== source || csv !== prevProps.csv) {
      if (app === "csv") {
        this.props.onSetData({ app, csv, store, params })
      } else {

        if (app === 'activitiesSearch') {
          const filterArray = ['locations', 'sectors', 'organizations'];
          this.props.loadFilters_({ filterArray, store, locale });
        }
        this.props.onLoadData({ app, source, store, params, locale })
      }
    }
  }

  render() {
    const { data, loading, error } = this.props

    if (data) {
      return <DataContext.Provider value={data}>{this.props.children}</DataContext.Provider>
    } else if (error) {
      return <Segment color={"red"}>
        <h1>500</h1>
        <p>Wasn't able to load data</p>
      </Segment>
    } else if (loading) {
      return (<Container>
        <h1>Data Loading</h1>
        <Loader inverted content='Loading' />

      </Container>)
    } else {

      return <Container>
        <Segment color={"red"}>
          <h1>404</h1>
          <p>Can't find this page</p>
        </Segment>
      </Container>
    }

    return null
  }
}

const mapStateToProps = (state, ownProps) => {
  const { store } = ownProps

  return {
    data: state.getIn(['data', ...store, 'data']),
    filters: state.getIn(['data', 'filters']),
    error: state.getIn(['data', ...store, 'error']),
    loading: state.getIn(['data', ...store, 'loading']),
  }
}

const mapActionCreators = {
  onSetData: setData,
  onLoadData: getData,
  loadFilters_: loadFilters
};

export default connect(mapStateToProps, mapActionCreators)(injectIntl(DataProvider));
