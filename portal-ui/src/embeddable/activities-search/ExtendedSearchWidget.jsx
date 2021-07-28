import React, { useState } from 'react';
import { Button, Dropdown, Form, Input, Pagination } from "semantic-ui-react";
import './ExtendedSearchWidget.scss';
import TopList from '../top-lists/TopList';
import Totals from '../totals/index.jsx';
import { loadSearchData } from "../reducers/data";
import { connect } from "react-redux";
import { injectIntl } from "react-intl";

const ExtendedSearchWidget = (props) => {
  const [activePage, setActivePage] = useState(1);
  const listDefinitions = [];
  const [selectedFilters, setSelectedFilters] = useState({});
  const [keyword, setKeyword] = useState(1);
  const { labels, data, store, loadData, data_locations, data_sectors, data_organizations } = props;
  const tableLabels = {};

  const fields = [];
  fields.push('project-title');
  fields.push("donor-agency")
  fields.push("primary-sector")
  fields.push('actual-commitments');
  fields.push('actual-disbursements');

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
    setActivePage(activePage);
    const filters = {};
    const pageSize = 10;
    const page = activePage;
    loadData({ filters, keyword, page, pageSize, store });
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
  const doSearchActivities = (e) => {

    const pageSize = 10;
    const filters = buildFilters();
    console.log(filters);
    loadData({ filters: {}, keyword, page: activePage, pageSize, store });
  }
  console.log(data_locations);
  debugger;
  return <>
    <div className={"search-widget"}>
      <div className="list-header">
        <h3>{labels.title}</h3>
      </div>
      <Form>
        <Form.Field>
          <label>{labels.description}</label>
          <Input placeholder={labels.hint} type='text' onChange={handleKeywordChange} />
        </Form.Field>
        <Form.Field>
          <label>Donor Agency</label>
          <Dropdown
            placeholder='Donor Agency'
            fluid
            multiple
            search
            selection
            options={populateDropDown(data_organizations, "Donor")}
            onChange={handleDropdownChange}
          />
        </Form.Field>
        <Form.Field>
          <label>Primary Sector</label>
          <Dropdown
            placeholder='Primary Sector'
            fluid
            multiple
            search
            selection
            options={populateDropDown(data_sectors, 'Primary Sectors')}
            onChange={handleDropdownChange}
          />
        </Form.Field>
        <Form.Field>
          <label>Secondary Sector</label>
          <Dropdown
            placeholder='Secondary Sector'
            fluid
            multiple
            search
            selection
            options={populateDropDown(data_sectors, 'Secondary Sectors')}
            onChange={handleDropdownChange}
          />
        </Form.Field>
        <Form.Field>
          <label>Locations</label>
          <Dropdown
            placeholder='Locations'
            fluid
            multiple
            search
            selection
            options={populateDropDown(data_locations, "Locations")}
            onChange={handleDropdownChange}
          />
        </Form.Field>
        <Button className="primary-button" type='link' onClick={doSearchActivities}>{labels.button}</Button>
      </Form>

    </div>
    <div>
      <div className="results-value">Activity
        result {pageFrom()} - {pageTo()} of {data.count}</div>
      <TopList data={data} labels={tableLabels} identity="activity-id" fields={fields} header isBigTable />
      <Pagination defaultActivePage={data.page} totalPages={data.totalpagecount}
                  onPageChange={handlePaginationChange} />
      <Totals/>
    </div>
  </>;

}

const mapStateToProps = (state, ownProps) => {
  const { store } = ownProps
  return {
    data: state.getIn(['data', ...store, 'data']),
    error: state.getIn(['data', ...store, 'error']),
    loading: state.getIn(['data', ...store, 'loading']),
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
