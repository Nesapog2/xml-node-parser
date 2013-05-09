//
//  ParserNode.m
//  NodeParser
//
//  Created by Robert Ryan on 5/9/13.
//  Copyright (c) 2013 Robert Ryan. All rights reserved.
//

#import "ParserNode.h"

@implementation ParserNode

- (void)addChild:(id)child
{
    if (!self.childNodes)
        self.childNodes = [NSMutableArray arrayWithObject:child];
    else
        [self.childNodes addObject:child];
}

// this is useful if you want to log a Node, just do:
//
// NSLog(@"%@", [node dictionary]);

- (NSDictionary *)dictionary
{
    NSMutableArray *array = [NSMutableArray array];
    for (ParserNode *node in self.childNodes)
    {
        [array addObject:[node dictionary]];
    }
    
    NSDictionary *dictionary = @{
                                 @"1.elementName" : self.elementName,
                                 @"2.attributes"  : (self.attributes ? self.attributes : [NSNull null]),
                                 @"3.value"       : (self.value ? self.value : [NSNull null]),
                                 @"4.children"    : array
                                 };
    
    return dictionary;
}

- (NSUInteger)count
{
    return [self.childNodes count];
}

- (id)objectAtIndexedSubscript:(NSUInteger)index
{
    ParserNode *child = self.childNodes[index];
    if (child)
    {
        if (child.value)
            return child.value;
        else
            return child;
    }
    
    return nil;
}

- (id)objectForKeyedSubscript:(NSString *)key
{
    for (ParserNode *child in self.childNodes)
    {
        if ([child.elementName isEqualToString:key])
        {
            if (child.value)
                return child.value;
            else
                return child;
        }
    }
    
    return nil;
}

@end
