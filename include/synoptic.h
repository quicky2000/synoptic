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
#ifndef SYNOPTIC_H
#define SYNOPTIC_H

#include "simple_gui.h"
#include "zone_owner_if.h"
#include "zone_container.h"
#include "zone_information.h"
#include "quicky_exception.h"
#include <iostream>
#include <map>
#include <set>

namespace synoptic
{
  class synoptic: protected simple_gui, public zone_owner_if
  {
  public:
    inline synoptic(const uint32_t & p_width,
		    const uint32_t & p_height);
    inline void set_pixel(const zone &,
                          const uint32_t & p_x,
                          const uint32_t & p_y,
                          const uint32_t & p_color);
    // Methods from zone_owner_if
    inline uint32_t get_color_code(const uint8_t & r,
				   const uint8_t & g,
				   const uint8_t & b);
    inline void paint(void);
    inline void pack(void);
    inline void to_refresh(const zone & p_zone);
    // End of methods from zone_owner_if

    inline void add_zone(const uint32_t & p_x,
                         const uint32_t & p_y,
                         zone & p_zone);
    inline void refresh(void);
  private:
    bool m_packed;
    zone_container m_zone_container;
    std::map<const zone * const,zone_information> m_zones;
    std::set<const zone *> m_zones_to_refresh;
  };

  //----------------------------------------------------------------------------
  synoptic::synoptic(const uint32_t & p_width,
		     const uint32_t & p_height):
    m_packed(false),
    m_zone_container("synoptic_pane",p_width,p_height)
      {
	createWindow(p_width,p_height);
      }
    //----------------------------------------------------------------------------
    void synoptic::add_zone(const uint32_t & p_x,
			    const uint32_t & p_y,
                            zone & p_zone)
    {
      m_zone_container.add_zone(p_x,p_y,p_zone);
    }

    //----------------------------------------------------------------------------
    void synoptic::paint(void)
    {
      m_zone_container.paint();
    }

    //----------------------------------------------------------------------------
    void synoptic::to_refresh(const zone & p_zone)
    {
      m_zones_to_refresh.insert(&p_zone);
    }

    //----------------------------------------------------------------------------
    void synoptic::set_pixel(const zone & p_zone,
                             const uint32_t & p_x,
                             const uint32_t & p_y,
                             const uint32_t & p_color)
    {
      std::map<const zone * const,zone_information>::const_iterator l_iter = m_zones.find(&p_zone);
      if(m_zones.end() == l_iter) throw quicky_exception::quicky_logic_exception("Unkown zone for pixel draw",__LINE__,__FILE__);
      if(!l_iter->first->contains(p_x,p_y))
        {
          throw quicky_exception::quicky_runtime_exception("Try to draw outside of zone",__LINE__,__FILE__);
        }
         
      this->set_pixel_without_lock(p_x + l_iter->second.get_x(),p_y + l_iter->second.get_y(),p_color);
    }

    //----------------------------------------------------------------------------
    uint32_t synoptic::get_color_code(const uint8_t & r,
                                      const uint8_t & g,
                                      const uint8_t & b)
    {
      return getColorCode(r,g,b);
    }

    //----------------------------------------------------------------------------
    void synoptic::pack(void)
    {
      m_packed = true;
      m_zone_container.collect_display_zones(m_zones);
    }

    //----------------------------------------------------------------------------
    void synoptic::refresh(void)
    {
      if(!m_packed)
        {
	  pack();
        }
      lock();
      for(std::set<const zone *>::const_iterator l_iter = m_zones_to_refresh.begin();
	  m_zones_to_refresh.end() != l_iter;
	  ++l_iter)
	{
	  std::map<const zone * const,zone_information>::const_iterator l_info_iter = m_zones.find(*l_iter);
	  if(m_zones.end() == l_info_iter) throw quicky_exception::quicky_logic_exception("Try to refresh unkwown zone",__LINE__,__FILE__);
          simple_gui::refresh(l_info_iter->second.get_x(),l_info_iter->second.get_y(),(*l_iter)->get_width(),(*l_iter)->get_height());
	}
      unlock();
      m_zones_to_refresh.clear();
    }
}
#endif // SYNOPTIC_H
//EOF
