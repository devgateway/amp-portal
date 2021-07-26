import React from 'react';
import DataProvider from "../data/DataProvider";
import { Container } from "semantic-ui-react";
import DataConsumer from "../data/DataConsumer";
import SearchWidget from "./SearchWidget";
import ExtendedSearchWidget from "./ExtendedSearchWidget";

const ActivitiesSearch = (props) => {
    const {
      'data-height': height = 500,
      'data-search-title': searchTitle = '',
      'data-search-description': searchDescription = '',
      'data-search-button': searchButton = 'Search',
      'data-search-hint': searchHint = '',
      'data-search-tooltip': searchTooltip,
      'data-search-extended-slug': searchExtendedSlug = 'search-results',
      'data-search-type': searchType = 'simpleSearch'

    }
      = props;
    const labels = {
      title: searchTitle,
      description: searchDescription,
      hint: searchHint,
      tooltip: searchTooltip,
      button: searchButton
    };
    let child;
    if (searchType==='simpleSearch'){
      child = (<SearchWidget height={height} labels={labels} searchExtendedSlug={searchExtendedSlug}/>);
    }else{
      child = (<ExtendedSearchWidget height={height} labels={labels} />);
    }
    const newSource = `activitiesSearch`;
    return <Container style={{ "height": `${height}px` }} className={"body"} fluid={true}>
      {child}
    </Container>
    /*NO DATA NEEDED FOR THIS COMPONENT return <DataProvider source={newSource} app={'activitiesSearch'} store={newSource} >
      <Container style={{ "height": `${height}px` }} className={"body"} fluid={true}><DataConsumer>
        {child}
      </DataConsumer></Container>
    </DataProvider>*/
  }
;
export default ActivitiesSearch;