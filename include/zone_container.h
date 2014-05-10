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
#ifndef ZONE_CONTAINER_H
#define ZONE_CONTAINER_H

#include "zone.h"
#include "zone_information.h"
#include "quicky_exception.h"
#include <map>
#include <set>
#include <string>

namespace synoptic
{
  class zone_container: public zone
  {
  public:
    inline zone_container(const std::string & p_name,
			  const uint32_t & p_width,
			  const uint32_t & p_height);
    inline void add_zone(const uint32_t & p_x,
                         const uint32_t & p_y,
                         zone & p_zone);
    inline void paint(void);

    inline void collect_display_zones(std::map<const zone * const,zone_information> & p_zones)const;

  private:
    std::map<const zone * const,zone_information> m_zone_informations;
    std::set<zone *> m_zones;
  };

  //----------------------------------------------------------------------------
  zone_container::zone_container(const std::string & p_name,
				 const uint32_t & p_width,
				 const uint32_t & p_height):
    zone(p_name,p_width,p_height)
    {
    }

  //----------------------------------------------------------------------------
    void zone_container::collect_display_zones(std::map<const zone * const,zone_information> & p_zones)const
    {
      for(std::map<const zone * const,zone_information>::const_iterator l_iter = m_zone_informations.begin();
	  m_zone_informations.end() != l_iter;
	  ++l_iter)
	{
	  std::map<const zone * const,zone_information> l_collected_zones;
	  l_iter->first->collect_display_zones(l_collected_zones);
	  for(std::map<const zone * const,zone_information>::const_iterator l_iter_collected = l_collected_zones.begin();
	      l_collected_zones.end() != l_iter_collected;
	      ++l_iter_collected)
	    {
	      p_zones.insert(std::map<const zone * const,zone_information>::value_type(l_iter_collected->first,zone_information(l_iter->second.get_x() + l_iter_collected->second.get_x(),l_iter->second.get_y() + l_iter_collected->second.get_y())));
	    }
	}
    }


  //----------------------------------------------------------------------------
    void zone_container::paint(void)
    {
      for(std::set<zone *>::iterator l_iter = m_zones.begin();
          m_zones.end() != l_iter;
	  ++l_iter)
	{
	  (*l_iter)->paint();
	}
    }

  //----------------------------------------------------------------------------
    void zone_container::add_zone(const uint32_t & p_x,
				  const uint32_t & p_y,
				  zone & p_zone)
    {
      if(p_x + p_zone.get_width() > get_width()) 
        throw quicky_exception::quicky_runtime_exception("In container \""+get_name()+"\" : Right part of zone \""+p_zone.get_name()+"\" is outside",__LINE__,__FILE__);
      if(p_y + p_zone.get_height() > get_height())
        throw quicky_exception::quicky_runtime_exception("In container \""+get_name()+"\" : Bottom part of zone \""+p_zone.get_name()+"\"is outside",__LINE__,__FILE__);
      // Check if there is any intersection with some existing zones
      for(std::map<const zone * const,zone_information>::const_iterator l_iter = m_zone_informations.begin();
	  l_iter != m_zone_informations.end();
	  ++l_iter)
	{
	  std::string l_zone_name = l_iter->first->get_name();
	  if(l_iter->first->contains(p_x - l_iter->second.get_x(),p_y - l_iter->second.get_y()) ) 
	    throw quicky_exception::quicky_runtime_exception("In container \""+get_name()+"\" : Top left corner of zone \""+p_zone.get_name()+" inside existing zone \""+l_zone_name+"\"",__LINE__,__FILE__);
	  if(l_iter->first->contains(p_x - l_iter->second.get_x() + p_zone.get_width() - 1 ,p_y - l_iter->second.get_y()) )
	    throw quicky_exception::quicky_runtime_exception("In container \""+get_name()+"\" : Top right corner of zone \""+p_zone.get_name()+"\" is inside existing zone \""+l_zone_name+"\"",__LINE__,__FILE__);
	  if(l_iter->first->contains(p_x - l_iter->second.get_x() , p_y + p_zone.get_height() - 1 - l_iter->second.get_y()) )
	    throw quicky_exception::quicky_runtime_exception("In container \""+get_name()+"\" : Bottom left corner of zone \""+p_zone.get_name()+" inside an existing zone \""+l_zone_name+"\"",__LINE__,__FILE__);
	  if(l_iter->first->contains(p_x - l_iter->second.get_x() + p_zone.get_width() - 1 ,p_y + p_zone.get_height() - 1 - l_iter->second.get_y()) )
	    throw quicky_exception::quicky_runtime_exception("In container \""+get_name()+"\" : Bottom right corner of zone \""+p_zone.get_name()+" inside an existing zone \""+l_zone_name+"\"",__LINE__,__FILE__);
	  if(p_zone.contains(l_iter->second.get_x() - p_x,l_iter->second.get_y() - p_y) )
	    throw quicky_exception::quicky_runtime_exception("In container \""+get_name()+"\" : Zone \""+p_zone.get_name()+"\" contains Top left corner of existing zone \""+l_zone_name+"\"",__LINE__,__FILE__);
	  if(p_zone.contains(l_iter->second.get_x() - p_x + l_iter->first->get_width() - 1,l_iter->second.get_y() - p_y) )
	    throw quicky_exception::quicky_runtime_exception("In container \""+get_name()+"\" : Zone \""+p_zone.get_name()+"\" contains Top Right corner of existing zone \""+l_zone_name+"\"",__LINE__,__FILE__);
	  if(p_zone.contains(l_iter->second.get_x() - p_x,l_iter->second.get_y() + l_iter->first->get_height() - 1 - p_y) )
	    throw quicky_exception::quicky_runtime_exception("In container \""+get_name()+"\" : Zone \""+p_zone.get_name()+"\" contains Bottom left corner of existing zone \""+l_zone_name+"\"",__LINE__,__FILE__);
	  if(p_zone.contains(l_iter->second.get_x() - p_x + l_iter->first->get_width() - 1,l_iter->second.get_y() + l_iter->first->get_height() - 1 - p_y))
	    throw quicky_exception::quicky_runtime_exception("In container \""+get_name()+"\" : Zone \""+p_zone.get_name()+"\" contains Bottom right corner of existing zone \""+l_zone_name+"\"",__LINE__,__FILE__);
          if(p_x > l_iter->second.get_x() && p_x + p_zone.get_width() < l_iter->second.get_x() + l_iter->first->get_width() && 
             p_y < l_iter->second.get_y() && p_y + p_zone.get_height() > l_iter->second.get_y() + l_iter->first->get_height())
	    throw quicky_exception::quicky_runtime_exception("In container \""+get_name()+"\": Internal overload between "+p_zone.get_name()+" and "+ l_zone_name,__LINE__,__FILE__);
          if(l_iter->second.get_x() > p_x && l_iter->second.get_x() + l_iter->first->get_width() < p_x + p_zone.get_width() && 
             p_y > l_iter->second.get_y() && p_y + p_zone.get_height() < l_iter->second.get_y() + l_iter->first->get_height())
	    throw quicky_exception::quicky_runtime_exception("In container \""+get_name()+"\" : Internal overload between "+p_zone.get_name()+" and "+ l_zone_name,__LINE__,__FILE__);
	}
      m_zone_informations.insert(std::map<const zone * const,zone_information>::value_type(&p_zone,zone_information(p_x,p_y)));
      m_zones.insert(&p_zone);
   }

}
#endif // ZONE_CONTAINER_H
//EOF
