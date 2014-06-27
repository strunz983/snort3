/*
** Copyright (C) 2014 Cisco and/or its affiliates. All rights reserved.
 * Copyright (C) 2002-2013 Sourcefire, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License Version 2 as
 * published by the Free Software Foundation.  You may not use, modify or
 * distribute this program under any other version of the GNU General
 * Public License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
// dt_rule.cc author Josh Rosenbaum <jorosenba@cisco.com>


#include "data/dt_rule.h"


Rule::Rule() :  num_hdr_data(0), bad_rule(false)
{
}

Rule::~Rule(){};


bool Rule::add_hdr_data(std::string data)
{
    if (num_hdr_data < hdr_data.size())
    {
        hdr_data[num_hdr_data] = data;
        num_hdr_data++;
        return true;
    }
    else
    {
        bad_rule = true;
        return false;
    }
}

bool Rule::add_option(std::string keyword)
{
    RuleOption* r = new RuleOption(keyword);
    options.push_back(r);
    return true;
}

bool Rule::add_option(std::string keyword, std::string data)
{
    RuleOption* r = new RuleOption(keyword, data);
    options.push_back(r);
    return true;
}

bool Rule::add_option_before_selected(RuleOption* selected_opt,
                                        std::string keyword,
                                        std::string val)
{
    for (auto r = options.begin(); r != options.end(); ++r)
    {
        if ((*r) == selected_opt)
        {
            RuleOption* new_opt = new RuleOption(keyword, val);
            options.insert(r, new_opt);
            return true;
        }
    }

    // impossible to occur.  Since a rule is already selected, we found this rule once.
    return false;
}

RuleOption* Rule::select_option(std::string opt_name)
{
    for (auto r = options.rbegin(); r != options.rend(); ++r)
        if (!opt_name.compare((*r)->get_name()))
            return (*r);
    return nullptr;
}

std::ostream &operator<<( std::ostream& out, const Rule &r)
{
    bool first_line = true;

    for(int i = 0; i < r.num_hdr_data; i++)
    {
        if (first_line)
            first_line = false;
        else
            out << " ";

        out << r.hdr_data[i];
    }

    out << " (";
    first_line = true;

    for (auto* r : r.options)
    {
        if (first_line)
            first_line = false;
        else
            out << ";";
        out << " " << (*r);
    }

    out << " )";

    return out;
}
