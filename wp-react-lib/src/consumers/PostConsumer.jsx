import React from 'react'
import {PostContext} from '../providers/Context'

const PostConsumer = (props) => {
    return (
        <PostContext.Consumer>
            {({posts,locale}) => {
                return posts && <React.Fragment>
                    {React.Children.map(props.children, (child => React.cloneElement(child, {posts: posts, locale})))}
                </React.Fragment>
            }}
        </PostContext.Consumer>
    )
}


export default PostConsumer
