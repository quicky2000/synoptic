/*    This file is part of synoptic
      The aim of this software is to provide synoptic reprenstation
      utilities
      Copyright (C) 2013  Julien Thevenon ( julien_thevenon at yahoo.fr )

      This program is free software: you can redistribute it and/or modify
      it under the terms of the GNU General Public License as published by
      the Free Software Foundation, either version 3 of the License, or
      (at your option) any later version.

      This program is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
      GNU General Public License for more details.

      You should have received a copy of the GNU General Public License
      along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#ifndef ZONE_H
#define ZONE_H

#include "zone_information.h"
#include <inttypes.h>
#include <string>
#include <map>

namespace synoptic
{


  /**
     Define a rectangular geometric zone
  **/
  class zone
  {
  public:
    inline zone(const std::string & p_name,
                const uint32_t & p_width,
                const uint32_t & p_height);
    inline const std::string & get_name(void)const;
    inline const uint32_t & get_width(void)const;
    inline const uint32_t & get_height(void)const;
    inline bool contains(const uint32_t & p_x,
			 const uint32_t & p_y)const;
    virtual void collect_display_zones(std::map<const zone * const,zone_information> & p_zones)const=0;
    virtual void paint(void)=0;
    virtual ~zone(void){}
  private:
    const std::string m_name;
    const uint32_t m_width;
    const uint32_t m_height;
  };
  //----------------------------------------------------------------------------
  zone::zone(const std::string & p_name,
             const uint32_t & p_width,
             const uint32_t & p_height):
    m_name(p_name),
    m_width(p_width),
    m_height(p_height)
      {
      }

    //----------------------------------------------------------------------------
    const std::string & zone::get_name(void)const
      {
	return m_name;
      }

    //----------------------------------------------------------------------------
    const uint32_t & zone::get_width(void)const
      {
        return m_width;
      }

    //----------------------------------------------------------------------------
    const uint32_t & zone::get_height(void)const
      {
        return m_height;
      }

    //----------------------------------------------------------------------------
    bool zone::contains(const uint32_t & p_x,
			const uint32_t & p_y)const
    {
      return p_x < m_width && p_y < m_height;
    }

}
#endif // ZONE_H
//EOF
