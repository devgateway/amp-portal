import React, { useEffect, useState } from 'react';
import { Button, Dropdown, Form, Input, Pagination } from "semantic-ui-react";
import './ExtendedSearchWidget.scss';
import TopList from '../top-lists/TopList';
import Totals from '../totals/index.jsx';
import { loadSearchData } from "../reducers/data";
import { connect } from "react-redux";
import { injectIntl } from "react-intl";
import { buildXlsData } from "../utils/exportUtils";

const ExtendedSearchWidget = (props) => {
  const [activePage, setActivePage] = useState(1);
  const listDefinitions = [];
  const [selectedFilters, setSelectedFilters] = useState({});
  const [keyword, setKeyword] = useState();
  const {
    labels,
    data,
    store,
    loadData,
    data_locations,
    data_sectors,
    data_organizations,
    filtersConfiguration
  } = props;
  const tableLabels = {};

  const fields = [];
  fields.push('activity-id');
  fields.push('project-title');
  fields.push("donor-agency")
  fields.push("primary-sector")
  fields.push("actual-start-date")
  fields.push('actual-commitments');
  fields.push('actual-disbursements');

  useEffect(() => {
      if (props.data_download) {
        buildXlsData(props.data_download, 'Aid Management platform', 'ActivityExport');
      }
    }, [props.data_download]
  )
  const populateDropDown = (filterObject, scheme) => {
    if (filterObject === undefined) {
      return [];
    }
    const keyPrefix = scheme.substring(0, 1);
    const listDefinition = filterObject.listDefinitions.find(ld => ld.name === scheme);
    listDefinitions[keyPrefix] = listDefinition;
    return getElements(filterObject.items[listDefinition.items], keyPrefix);
  }
  const getElements = (originalArray, keyPrefix) => {
    const elements = [];
    originalArray.forEach(s => {
      let level = 1;
      addToMap(s, elements, '', level, keyPrefix);
    })
    return elements;
  }
  const addToMap = (object, arrayOfObjects, ancestor, level, keyPrefix) => {
    arrayOfObjects.push({
      key: `${keyPrefix}_${object.id}${level}`,
      text: `${ancestor}${object.name}`,
      value: `${level}_${object.id}`,
      level: level,
      keyPrefix: keyPrefix,
      id: object.id,
    });
    if (object.children) {
      object.children.forEach(c => addToMap(c, arrayOfObjects, `${ancestor}  ${object.name} ->`, level + 1, keyPrefix))
    }
  }
  const pageFrom = () => {
    return 1 + (data.page - 1) * data.recordsperpage;
  }
  const pageTo = () => {
    const to = 10 + (data.page - 1) * data.recordsperpage;
    return to > data.count ? data.count : to;
  }
  const handleKeywordChange = (e, { value }) => {
    setKeyword(value);
  }
  const handlePaginationChange = (e, { activePage }) => {
    callSearchActivities(false);
  };
  const handleDropdownChange = (e, { value, options }) => {
    if (value) {
      const selectedOptions = options.filter(o => value.includes(o.value));
      //keyprefix is the same for all we just pick the first one
      setSelectedFilters(selectedFiltersOld => {
        const newSelectedFilters = { ...selectedFiltersOld }
        newSelectedFilters[selectedOptions[0].keyPrefix] = selectedOptions;
        return newSelectedFilters;
      })
    }
  }
  const buildFilters = () => {
    const filters = {};
    Object.keys(selectedFilters).forEach(k => {
      selectedFilters[k].forEach(l => {
        if (filters[listDefinitions[k].filterIds[l.level - 1]] === undefined) {
          filters[listDefinitions[k].filterIds[l.level - 1]] = [l.id];
        }
        filters[listDefinitions[k].filterIds[l.level - 1]].push();
      })
    });
    return filters;
  }
  const callSearchActivities = (isDownload) => {
    loadData({
      filters: buildFilters(),
      keyword,
      page: activePage,
      pageSize: data.recordsperpage,
      store,
      currency: data['Currency'],
      isDownload
    });
  }
  const doSearchActivities = (e) => {
    callSearchActivities(false);
  }
  const exportData = () => {
    callSearchActivities(true);
  }
  return <>
    <div className={"search-widget"}>
      <div className="list-header">
        <h3>{labels.title}</h3>
      </div>
      <Form className="advanced-search">
        <Form.Field>
          <label>{labels.description}</label>
          <Input placeholder={labels.hint} type='text' onChange={handleKeywordChange} />
        </Form.Field>
        {filtersConfiguration.donorFilters.enabled && (<Form.Field>
          <label>{filtersConfiguration.donorFilters.title}</label>
          <Dropdown
            placeholder={filtersConfiguration.donorFilters.placeholder}
            fluid
            multiple
            search
            selection
            options={populateDropDown(data_organizations, "Donor")}
            onChange={handleDropdownChange}
          />
        </Form.Field>)}
        {filtersConfiguration.primarySectorFilters.enabled && (
          <Form.Field>
            <label>{filtersConfiguration.primarySectorFilters.title}</label>
            <Dropdown
              placeholder={filtersConfiguration.primarySectorFilters.placeholder}
              fluid
              multiple
              search
              selection
              options={populateDropDown(data_sectors, 'Primary Sectors')}
              onChange={handleDropdownChange}
            />
          </Form.Field>)
        }
        {filtersConfiguration.secondarySectorFilters.enabled && (<Form.Field>
          <label>{filtersConfiguration.secondarySectorFilters.title}r</label>
          <Dropdown
            placeholder={filtersConfiguration.primarySectorFilters.placeholder}
            fluid
            multiple
            search
            selection
            options={populateDropDown(data_sectors, 'Secondary Sectors')}
            onChange={handleDropdownChange}
          />
        </Form.Field>)}
        {filtersConfiguration.locationFilters.enabled && (<Form.Field>
          <label>{filtersConfiguration.locationFilters.title}</label>
          <Dropdown
            placeholder={filtersConfiguration.locationFilters.placeholder}
            fluid
            multiple
            search
            selection
            options={populateDropDown(data_locations, "Locations")}
            onChange={handleDropdownChange}
          />
        </Form.Field>)}
        <Button className="primary-button" type='link' onClick={doSearchActivities}>{labels.button}</Button>
      </Form>

    </div>
    <div className="results-wrapper">
      <div className="results-value">Activity
        result {pageFrom()} - {pageTo()} of {data.count}</div>
      <TopList data={data} labels={tableLabels} identity="activity-id" fields={fields} header isBigTable
               exportData={exportData} linkField="activity-id" />
      <Pagination defaultActivePage={data.page} totalPages={data.totalpagecount}
                  onPageChange={handlePaginationChange} />

    </div>
    <div><Totals data={data} /></div>
  </>;

}

const mapStateToProps = (state, ownProps) => {
  const { store } = ownProps
  return {
    settings: state.getIn(['data', ...['amp-settings'], 'data']),
    data: state.getIn(['data', ...store, 'data']),
    error: state.getIn(['data', ...store, 'error']),
    loading: state.getIn(['data', ...store, 'loading']),
    data_download: state.getIn(['data', ...(store + '-download'), 'data']),
    error_download: state.getIn(['data', ...(store + '-download'), 'error']),
    loading_download: state.getIn(['data', ...(store + '-download'), 'loading']),
    data_locations: state.getIn(['data', ...(store + 'locations'), 'data']),
    error_locations: state.getIn(['data', ...(store + 'locations'), 'error']),
    loading_locations: state.getIn(['data', ...(store + 'locations'), 'loading']),
    data_sectors: state.getIn(['data', ...(store + 'sectors'), 'data']),
    error_sectors: state.getIn(['data', ...(store + 'sectors'), 'error']),
    loading_sectors: state.getIn(['data', ...(store + 'sectors'), 'loading']),
    data_organizations: state.getIn(['data', ...(store + 'organizations'), 'data']),
    error_organizations: state.getIn(['data', ...(store + 'organizations'), 'error']),
    loading_organizations: state.getIn(['data', ...(store + 'organizations'), 'loading']),

  }
}

const mapActionCreators = {
  loadData: loadSearchData
};

export default connect(mapStateToProps, mapActionCreators)(injectIntl(ExtendedSearchWidget));
