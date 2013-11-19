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
#ifndef ZONE_INFORMATION_H
#define ZONE_INFORMATION_H

#include <inttypes.h>

namespace synoptic
{
  class zone_information
  {
  public:
    inline zone_information(const uint32_t & p_x,
			    const uint32_t & p_y);
    inline const uint32_t & get_x(void)const;
    inline const uint32_t get_y(void)const;
  private:
    const uint32_t m_x;
    const uint32_t m_y;
  };

  //----------------------------------------------------------------------------
  zone_information::zone_information(const uint32_t & p_x,
				     const uint32_t & p_y):
    m_x(p_x),
    m_y(p_y)
      {
      }

  //----------------------------------------------------------------------------
    const uint32_t & zone_information::get_x(void)const
      {
	return m_x;
      }

  //----------------------------------------------------------------------------
    const uint32_t zone_information::get_y(void)const
    {
      return m_y;
    }
}

#endif // ZONE_INFORMATION_H
//EOF
