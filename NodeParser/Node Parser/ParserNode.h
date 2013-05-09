//
//  ParserNode.h
//  NodeParser
//
//  Created by Robert Ryan on 5/9/13.
//  Copyright (c) 2013 Robert Ryan. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * This is a object that represents a "node" of the XML structure parsed by the `XMLNodeParser` class.
 *
 * This reflects the recursive nature of XML files, whereby every node is represented by either:
 *
 * - a `NSString` called `value`; or
 *
 * - an array, called `childNodes`, of `ParserNode` objects) representing the sub-elements
 *   of the XML feed.
 *
 * For usage example, please refer to the `XMLNodeParser` documentation.
 *
 * @see `XMLNodeParser`
 *
 */

@interface ParserNode : NSObject

///---------------------------------------------------------------------------------------
/// @name Properties
///---------------------------------------------------------------------------------------

/// The XML element name

@property (nonatomic, strong) NSString *elementName;

/// The XML attributes

@property (nonatomic, strong) NSDictionary *attributes;

/// If the element was a simple text string, this is the value of that string.
///
/// If the element has sub-elements, this will be `nil`.

@property (nonatomic, strong) NSMutableString *value;

/// An array of `ParserNode` objects representing the sub-elements of this element.
///
/// If there were no sub elements, this will be `nil`.

@property (nonatomic, strong) NSMutableArray *childNodes;

///---------------------------------------------------------------------------------------
/// @name Methods
///---------------------------------------------------------------------------------------

/// A dictionary representing the contents of this `ParserNode`
///
/// This is useful if you want to do a simple `NSLog` of the results, e.g.,
///
///    NSLog(@"%@", [node description]);

- (NSDictionary *)dictionary;

/// The number of child elements for this node. If there are no child elements,
/// this will be `0`.

- (NSUInteger)count;

/// This permits the use of "Modern Objective-C" boxing syntax for a zero-based numeric index.
///
/// For example, if there were child nodes, this returns the first node:
///
///    id child = node[0];
///
/// @param index A the zero-based index
///
/// @return If that child, itself, has an array of nodes, this will return a `ParserNode` object.
///
/// If the child has no child nodes itself, this simply returns a `NSString` of the value.
///
/// If no matching child object found, this returns `nil`.
///
/// @warning The use of the "[]" syntax requires Xcode 4.5 or greater. For earlier compilers,
/// rather than
///
///    id child = node[0];
///
/// you would have to use:
///
///    id child = [node objectAtIndexedSubscript:0];

- (id)objectAtIndexedSubscript:(NSUInteger)index;

/// This permits the use of "Modern Objective-C" boxing syntax for a `NSString` key.
///
/// For example, if there were child nodes, this returns the node whose `elementName`
/// matches the:
///
///    id child = node[@"elementName"];
///
/// @param key A the `NSString` value of the `elementName` of the child node.
///
/// @return If this finds a child that, itself, has an array of nodes, this will return a `ParserNode` object.
/// If the matching child has no child nodes itself, this simply returns a `NSString` of the `value` of this node.
///
/// If no matching child object found, this returns `nil`.
///
/// @warning The use of the "[]" syntax requires Xcode 4.5 or greater. For earlier compilers,
/// rather than
///
///    id child = node[@"elementName"];
///
/// you would have to use:
///
///    id child = [node objectForKeyedSubscript:@"elementName"];

- (id)objectForKeyedSubscript:(NSString *)key;

/// This is used by the parser to add a child node to the `ParserNode` object.
///
/// @param child A `ParserNode` object to add as a child of this `ParserNode` object.

- (void)addChild:(id)child;

@end
