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
#include "zone.h"
#include "zone_information.h"
#include "quicky_exception.h"
#include <map>
#include <set>
#include <iostream>

namespace synoptic
{
  class synoptic: protected simple_gui, public zone_owner_if
  {
  public:
    inline synoptic(const uint32_t & p_width,
		    const uint32_t & p_height);
    inline void add_zone(const uint32_t & p_x,
                         const uint32_t & p_y,
                         const zone & p_zone);
    inline void set_pixel(const zone &,
                          const uint32_t & p_x,
                          const uint32_t & p_y,
                          const uint32_t & p_color);
    // Methods from zone_owner_if
    uint32_t get_color_code(const uint8_t & r,
                            const uint8_t & g,
                            const uint8_t & b);
    inline void refresh(void);
    inline void to_refresh(const zone & p_zone);
  private:
    std::map<const zone * const,zone_information> m_zones;
    std::set<const zone *> m_zones_to_refresh;
  };

  //----------------------------------------------------------------------------
  synoptic::synoptic(const uint32_t & p_width,
		     const uint32_t & p_height)
    {
      createWindow(p_width,p_height);
    }

  //----------------------------------------------------------------------------
    void synoptic::add_zone(const uint32_t & p_x,
                            const uint32_t & p_y,
                            const zone & p_zone)
    {
      if(p_x + p_zone.get_width() > get_width()) throw quicky_exception::quicky_runtime_exception("Right part of zone is outside",__LINE__,__FILE__);
      if(p_y + p_zone.get_height() >get_height()) throw quicky_exception::quicky_runtime_exception("Bottom part of zone is outside",__LINE__,__FILE__);
      // Check if there is any intersection with some existing zones
      for(std::map<const zone * const,zone_information>::const_iterator l_iter = m_zones.begin();
	  l_iter != m_zones.end();
	  ++l_iter)
	{
	  if(l_iter->first->contains(p_x - l_iter->second.get_x(),p_y - l_iter->second.get_y()) ) throw quicky_exception::quicky_runtime_exception("Top left corner inside an existing zone",__LINE__,__FILE__);
	  if(l_iter->first->contains(p_x - l_iter->second.get_x() + p_zone.get_width() - 1 ,p_y - l_iter->second.get_y()) ) throw quicky_exception::quicky_runtime_exception("Top right corner inside an existing zone",__LINE__,__FILE__);
	  if(l_iter->first->contains(p_x - l_iter->second.get_x() , p_y + p_zone.get_height() - 1 - l_iter->second.get_y()) ) throw quicky_exception::quicky_runtime_exception("Bottom left corner inside an existing zone",__LINE__,__FILE__);
	  if(l_iter->first->contains(p_x - l_iter->second.get_x() + p_zone.get_width() - 1 ,p_y + p_zone.get_height() - 1 - l_iter->second.get_y()) ) throw quicky_exception::quicky_runtime_exception("Bottom right corner inside an existing zone",__LINE__,__FILE__);
	  if(p_zone.contains(l_iter->second.get_x() - p_x,l_iter->second.get_y() - p_y) ) throw quicky_exception::quicky_runtime_exception("Zone contains Top left corner of existing zone",__LINE__,__FILE__);
	  if(p_zone.contains(l_iter->second.get_x() - p_x + l_iter->first->get_width() - 1,l_iter->second.get_y() - p_y) ) throw quicky_exception::quicky_runtime_exception("Zone contains Top Right corner of existing zone",__LINE__,__FILE__);
	  if(p_zone.contains(l_iter->second.get_x() - p_x,l_iter->second.get_y() + l_iter->first->get_height() - 1 - p_y) ) throw quicky_exception::quicky_runtime_exception("Zone contains Bottom left corner of existing zone",__LINE__,__FILE__);
	  if(p_zone.contains(l_iter->second.get_x() - p_x + l_iter->first->get_width() - 1,l_iter->second.get_y() + l_iter->first->get_height() - 1 - p_y)) throw quicky_exception::quicky_runtime_exception("Zone contains Bottom right corner of existing zone",__LINE__,__FILE__);
	}
      m_zones.insert(std::map<const zone * const,zone_information>::value_type(&p_zone,zone_information(p_x,p_y)));
      m_zones_to_refresh.insert(&p_zone);
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
    void synoptic::refresh(void)
    {
      // simple_gui::refresh();return;
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
