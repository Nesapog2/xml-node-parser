//
//  XMLNodeParser.m
//  NodeParser
//
//  Created by Robert Ryan on 5/9/13.
//  Copyright (c) 2013 Robert Ryan. All rights reserved.
//

#import "XMLNodeParser.h"

@interface XMLNodeParser () <NSXMLParserDelegate>

@property (nonatomic, strong) ParserNode *currentNode;
@property (nonatomic, strong) NSIndexPath *currentIndexPath;

@end

@implementation XMLNodeParser

#pragma mark - Initializer methods

// these initializer methods basically just call the standard
// initializer methods, but also set their delegate to this
// object

- (id)init
{
    self = [super init];
    if (self) {
        self.delegate = self;
    }
    return self;
}

- (id)initWithContentsOfURL:(NSURL *)url
{
    self = [super initWithContentsOfURL:url];
    if (self) {
        self.delegate = self;
    }
    return self;
}

- (id)initWithData:(NSData *)data
{
    self = [super initWithData:data];
    if (self) {
        self.delegate = self;
    }
    return self;
}

- (id)initWithStream:(NSInputStream *)stream
{
    self = [super initWithStream:stream];
    if (self) {
        self.delegate = self;
    }
    return self;
}

- (ParserNode *) selectNodeForIndexPath:(NSIndexPath *)indexPath
{
    ParserNode *node = self.results;
    
    for (NSInteger i = 0; i < indexPath.length; i++)
        node = node.childNodes[[indexPath indexAtPosition:i]];
    
    return node;
}

#pragma mark - NSXMLParserDelegate methods

- (void)parser:(NSXMLParser *)parser didStartElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName attributes:(NSDictionary *)attributeDict
{
    ParserNode *node = [[ParserNode alloc] init];
    node.elementName = elementName;
    node.attributes = attributeDict;
    
    if (self.currentNode)
    {
        NSUInteger lastIndex = [self.currentNode.childNodes count];
        [self.currentNode addChild:node];
        self.currentIndexPath = [self.currentIndexPath indexPathByAddingIndex:lastIndex];
    }
    else
    {
        self.results = node;
        self.currentIndexPath = [[NSIndexPath alloc] init];
    }
    
    self.currentNode = node;
}

- (void)parser:(NSXMLParser *)parser foundCharacters:(NSString *)string
{
    NSMutableString *mutableString = self.currentNode.value;
    
    if (!mutableString)
    {
        mutableString = [NSMutableString stringWithString:string];
        self.currentNode.value = mutableString;
    }
    else
    {
        [self.currentNode.value appendString:string];
    }
}

- (void)parser:(NSXMLParser *)parser didEndElement:(NSString *)elementName namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName
{
    // ok, if we're closing a element, and we found sub-elements, then any string retrieved by
    // found characters is probably just the whitespace around the tags, and we can throw it away
    
    if (self.currentNode.childNodes)
        self.currentNode.value = nil;
    
    // let's pop off the last node
    
    self.currentIndexPath = [self.currentIndexPath indexPathByRemovingLastIndex];
    self.currentNode = [self selectNodeForIndexPath:self.currentIndexPath];
}

@end
