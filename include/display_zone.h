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
#ifndef DISPLAY_ZONE_H
#define DISPLAY_ZONE_H

#include "zone.h"
#include "zone_owner_if.h"
#include "zone_container.h"
namespace synoptic
{
  /**
     Base class for zone allowing to display information
  **/
  class display_zone: public zone
  {
  public:
    inline display_zone(zone_owner_if &,
			const std::string & p_name,
			const uint32_t & p_width,
			const uint32_t & p_height);
    inline void paint(void);
    inline void collect_display_zones(std::map<const zone * const,zone_information> & p_zones)const;
  protected:
    inline const zone_owner_if & get_owner(void)const;
    inline zone_owner_if & get_owner(void);
    inline void set_pixel(const uint32_t & p_x,
                          const uint32_t & p_y,
                          const uint32_t & p_color);
  private:
    virtual void internal_paint(void)=0;
    zone_owner_if & m_owner;
  };

  //----------------------------------------------------------------------------
  display_zone::display_zone(zone_owner_if & p_owner,
			     const std::string & p_name,
			     const uint32_t & p_width,
			     const uint32_t & p_height):
    zone(p_name,p_width,p_height),
    m_owner(p_owner)
      {
      }

    //----------------------------------------------------------------------------
    void display_zone::collect_display_zones(std::map<const zone * const,zone_information> & p_zones)const
    {
      p_zones.insert(std::map<const zone * const,zone_information>::value_type(this,zone_information(0,0)));
    }

    //----------------------------------------------------------------------------
    void display_zone::paint(void)
    {
      m_owner.to_refresh(*this);
      this->internal_paint();
    }

    //----------------------------------------------------------------------------
    const zone_owner_if & display_zone::get_owner(void)const
      {
	return m_owner;
      }
    //----------------------------------------------------------------------------
    zone_owner_if & display_zone::get_owner(void)
      {
	return m_owner;
      }
    //----------------------------------------------------------------------------
    void display_zone::set_pixel(const uint32_t & p_x,
                         const uint32_t & p_y,
                         const uint32_t & p_color)
    {
      m_owner.set_pixel(*this,p_x,p_y,p_color);
    }

}
#endif // DISPLAY_ZONE_H
//EOF
