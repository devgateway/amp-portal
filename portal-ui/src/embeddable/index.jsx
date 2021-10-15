//import  React from 'react'
import asyncComponent from "../AsyncComponent";

import data from './reducers/data'
import embeddable from './reducers/embeddable'

const TabbedPosts = asyncComponent(() => import("./tabbedposts/"));
const PostsCarousel = asyncComponent(() => import("./postscarousel/"));
const PageGallery = asyncComponent(() => import("./pagegallery/"));
const PageModules = asyncComponent(() => import("./pagemodules/"));
const FeaturedTabs = asyncComponent(() => import("./featuredtabs/"));
const InlineList = asyncComponent(() => import("./inlinelist/"));
const Chart = asyncComponent(() => import("./chart/"));
const NewsLetter = asyncComponent(() => import("./newsletter/"));
const ShowcaseForm = asyncComponent(() => import("./showcase/"));
const Body = asyncComponent(() => import("./body/"));
const Filter = asyncComponent(() => import("./filter/"));
const Download = asyncComponent(() => import("./download/"));
const Map = asyncComponent(() => import("./map/"));
const TopLists = asyncComponent(() => import("./top-lists/"));
const ActivitiesSearch = asyncComponent(() => import("./activities-search/"));
export const reducers = {
  data,
  embeddable
}


const components = {
  pageGallery: PageGallery,
  postsCarousel: PostsCarousel,
  chart: Chart,
  filter: Filter,
  showCaseForm: ShowcaseForm,
  newsLetter: NewsLetter,
  body: Body,
  tabbedPosts: TabbedPosts,
  pageModules: PageModules,
  featuredTabs: FeaturedTabs,
  inlineList: InlineList,
  download: Download,
  map: Map,
  topLists: TopLists,
  activitiesSearch: ActivitiesSearch
}

export const getComponentByNameIgnoreCase = (name) => {

  const k = Object.keys(components).filter(value => value.toLowerCase() === name.toLowerCase())
  return components[k]
}
